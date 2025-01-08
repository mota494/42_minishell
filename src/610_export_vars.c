/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_export_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:34:21 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 10:19:48 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_var(char *toadd)
{
	char	*var_name;
	int		i;
	char	*var_value;

	var_name = initalize_str();
	var_value = initalize_str();
	i = 0;
	while (toadd[i] && toadd[i] != '=')
	{
		var_name = strjoinchr(var_name, toadd[i]);
		i++;
	}
	i++;
	while (toadd[i])
	{
		var_value = strjoinchr(var_value, toadd[i]);
		i++;
	}
	change_env_value(var_name, var_value);
	free(var_name);
	free(var_value);
}

void	var_no_equal(t_c_envp *n_env, int pos, char *toadd)
{
	n_env[pos].var_name = ft_strdup(toadd);
	n_env[pos].var_value = initalize_str();
	n_env[pos].equal = 0;
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

void	add_env_vars(t_c_envp *n_env, t_token *cmd, int i, t_shell *sh)
{
	cmd = cmd->next;
	while (cmd && cmd->type == string)
	{
		if (!check_var_name(cmd->cmd_line) || cmd->cmd_line[0] == '=')
		{
			printf("minishell: export: %s, not a valid identifier\n",
				cmd->cmd_line);
			sh->error_code = 1;
		}
		else if (var_exist(cmd->cmd_line) && check_equal(cmd->cmd_line))
			change_env_var(cmd->cmd_line);
		else if (!var_exist(cmd->cmd_line) && !check_equal(cmd->cmd_line))
		{
			var_no_equal(n_env, i, cmd->cmd_line);
			i++;
		}
		else if (!var_exist(cmd->cmd_line) && check_equal(cmd->cmd_line))
		{
			add_var(n_env, i, cmd->cmd_line);
			i++;
		}
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
	ret_env(n_env);
	add_env_vars(n_env, cmd, size_env(n_env), sh);
	if (sh->error_code != 1)
		sh->error_code = 0;
	free(b_env);
	sh->c_envp = n_env;
}
