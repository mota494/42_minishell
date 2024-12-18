/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   501_redirect_and_wait.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:11:19 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/12/18 15:13:57 by mloureir         ###   ########.fr       */
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
	}
	cmd->error_code = wstatus;
	return (0);
}
