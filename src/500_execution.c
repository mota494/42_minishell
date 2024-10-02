/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:20:50 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/10/01 15:48:30 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// /**printf para debug - remover
//  * malloc here!
// */
// int	create_pipes(t_shell *cmd)
// {
// 	int	i;

// 	cmd->p_fds = (t_fd *)malloc(sizeof(t_fd) * (cmd->n_inputs - 1));
// 	if (!cmd->p_fds)
// 	{
// 		printf("Memory allocation issue - pipe fds");
// 		return (1);
// 	}
// 	i = -1;
// 	while (++ i < cmd->n_inputs - 1)
// 	{
// 		if (pipe(cmd->p_fds[i].fd))
// 		{
// 			printf("Error creating pipes");
// 			return (2);
// 		}
// 	}
// 	return (0);
// }

// int	alloc_pids(t_shell *cmd)
// {
// 	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * cmd->n_inputs);
// 	if (!cmd->pids)
// 	{
// 		printf("Memory allocation issue - alloc_pids");
// 		return (1);
// 	}
// 	return (0);
// }

// int	fork_and_execute(t_shell *cmd)
// {
// 	int	i;
// 	int	child_status;

// 	i = -1;
// 	while (++ i < cmd->n_inputs)
// 	{
// 		cmd->pids[i] = fork();
// 		if (cmd->pids[i] == -1)
// 		{
// 			printf("fork issue");
// 			return (1);
// 		}
// 		if (cmd->pids[i] == 0)
// 		{
// 			if (i == 0)
// 				first_redirect(cmd);
// 			else if (i == cmd->n_inputs - 1)
// 				last_redirect(cmd, i);
// 			else
// 				std_redirect(cmd, i);
// 			close_fds(cmd);
// 			run_cmdx();
// 		}
// 	}
// 	close_fds(cmd);
// 	child_status = wait_for_child(cmd);
// 	//free_mem();
// }
