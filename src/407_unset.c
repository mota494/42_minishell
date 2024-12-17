/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   407_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/17 14:51:34 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	old_env_free(t_c_envp *c_env)
{
	int	i;

	i = 0;
	while (c_env[i].var_name)
	{
		free(c_env[i].var_name);
		free(c_env[i].var_value);
		i++;
	}
}

void	copy_env_values(t_c_envp *n_env, t_c_envp *b_env, int pos_n, int pos_b)
{
	n_env[pos_n].var_name = ft_strdup(b_env[pos_b].var_name);
	if (b_env[pos_b].var_value)
		n_env[pos_n].var_value = ft_strdup(b_env[pos_b].var_value);
	n_env[pos_n].equal = b_env[pos_b].equal;
}

t_c_envp	*unset_env_value(char *var_value)
{
	t_c_envp	*b_env;
	t_c_envp	*n_env;
	t_count		c;

	b_env = ret_env(NULL);
	n_env = ft_calloc(size_env(b_env), sizeof(t_c_envp));
	start_counters(&c);
	while (b_env[c.d_i].var_name)
	{
		if (sstrcmp(var_value, b_env[c.d_i].var_name))
			c.d_i++;
		else
		{
			copy_env_values(n_env, b_env, c.i_i, c.d_i);
			c.d_i++;
			c.i_i++;
		}
	}
	ret_env(n_env);
	old_env_free(b_env);
	free(b_env);
	return (n_env);
}

void	unset_env(t_shell *cmd)
{
	int		args;
	t_token	*temp;

	temp = cmd->token->next;
	args = count_args(temp);
	if (args <= 0)
	{
		cmd->error_code = 0;
		return ;
	}
	if (temp->cmd_line[0] == '-')
	{
		printf("Minishell: unset: -%c: invalid option\n", temp->cmd_line[1]);
		cmd->error_code = 2;
		return ;
	}
	while (args > 0)
	{
		if (get_env(temp->cmd_line))
			cmd->c_envp = unset_env_value(temp->cmd_line);
		temp = temp->next;
		args--;
	}
	cmd->error_code = 0;
}
