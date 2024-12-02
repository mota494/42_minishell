/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   406_export_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:34:21 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/02 09:54:25 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_var(t_c_envp *n_env, int pos, char *toadd)
{
	t_count	c;

	start_counters(&c);
	n_env[pos].var_name = initalize_str();
	n_env[pos].var_value = initalize_str();
	while (toadd[c.d] && toadd[c.d] != '=')
	{
		n_env[pos].var_name = strjoinchr(n_env[pos].var_name, toadd[c.d]);
		c.d++;
	}
	c.d++;
	n_env[pos].equal = '=';
	while (toadd[c.d])
	{
		n_env[pos].var_value = strjoinchr(n_env[pos].var_value, toadd[c.d]);
		c.d++;
	}
}

int	check_var_name(char *str)
{
	if (ft_isalpha(str[0]) == 1 || str[0] == '_')
		return (1);
	else
		return (0);
}

void	add_env_vars(t_c_envp *n_env, t_token *cmd, int i)
{
	cmd = cmd->next;
	while (cmd && cmd->type == string)
	{
		if (check_equal(cmd->cmd_line) == 0)
		{
			n_env[i].var_name = ft_strdup(cmd->cmd_line);
			n_env[i].var_value = initalize_str();
			n_env[i].equal = 0;
		}
		else if (check_var_name(cmd->cmd_line) == 0)
			printf("minishell: export: %s, not a valid identifier", cmd->cmd_line);
		else
			add_var(n_env, i, cmd->cmd_line);
		i++;
		cmd = cmd->next;
	}
	n_env[i].var_name = NULL;
	n_env[i].var_value = NULL;
}

void	export_new(int num_args, t_token *cmd, t_shell *sh)
{
	t_c_envp	*b_env;
	t_c_envp	*n_env;
	int			i;

	i = 0;
	b_env = ret_env(NULL);
	n_env = ft_calloc(num_args + 1 + size_env(b_env), sizeof(t_c_envp));
	while (b_env[i].var_name)
	{
		n_env[i].var_name = ft_strdup(b_env[i].var_name);
		free(b_env[i].var_name);
		if (b_env[i].var_value)
		{
			n_env[i].var_value = ft_strdup(b_env[i].var_value);
			free(b_env[i].var_value);
		}
		n_env[i].equal = b_env[i].equal;
		i++;
	}
	add_env_vars(n_env, cmd, size_env(n_env));
	free(b_env);
	ret_env(n_env);
	sh->c_envp = n_env;
}
