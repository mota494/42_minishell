/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   005_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:37:46 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/18 10:58:35 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *cmd)
{
	t_token	*temp;

	while (cmd->token)
	{
		temp = cmd->token;
		cmd->token = cmd->token->next;
		free(temp->cmd_line);
		free(temp->orig_line);
		free(temp);
	}
	free_pids(cmd);
	cmd->token = NULL;
}

void	free_env(t_shell *cmd)
{
	t_count		c;
	t_c_envp	*b_env;

	b_env = ret_env(NULL);
	start_counters(&c);
	while (b_env[c.i].var_name)
	{
		free(b_env[c.i].var_name);
		free(b_env[c.i].var_value);
		c.i++;
	}
	free(cmd->c_envp);
}

void	free_pids(t_shell *cmd)
{
	if (cmd->n_inputs > 1 || cmd->n_command >= 1)
		free(cmd->pids);
}
