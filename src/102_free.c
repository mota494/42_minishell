/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   102_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:37:46 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/13 11:27:17 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_shell *cmd)
{
	t_count	c;

	start_counters(&c);
	while (cmd->c_envp[c.i].id != -1)
	{
		if (sstrcmp("SHLVL", cmd->c_envp[c.i].var_name))
			free(cmd->c_envp[c.i].var_value);
		free(cmd->c_envp[c.i].var_name);
		c.i++;
	}
	free(cmd->c_envp);
}
