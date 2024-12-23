/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   501_redirect_and_wait.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:11:19 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/12/23 13:40:49 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_for_child(t_shell *cmd)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < cmd->n_inputs)
	{
		waitpid(cmd->pids[i], &wstatus, 0);
		cmd->error_code = wstatus;
		if (wstatus == 131)
			return_last_signal(SIGQUIT);
	}
	return (0);
}
