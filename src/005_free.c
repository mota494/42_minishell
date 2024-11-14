/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   005_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:37:46 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/14 17:40:58 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_shell *cmd)
{
	t_count	c;
	t_c_envp *b_env;

	b_env = ret_env(NULL);
	start_counters(&c);
	while (b_env[c.i].id != - 1)
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
