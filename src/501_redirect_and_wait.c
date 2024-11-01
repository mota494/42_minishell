/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   501_redirect_and_wait.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:11:19 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/10/18 14:23:25 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Verificar redirects (< > >>)
antes ou depois do comando dentro dessas funcoes? */

/** writes output on the writing end of pipe instead of on stdout
 ** still reads input from stdin */
void	first_redirect(t_shell *cmd)
{
	dup2(cmd->p_fds[0].fd[1], STDOUT_FILENO);
	close(cmd->p_fds[0].fd[1]);
}

/** reads input from the last pipe readind end 
 ** still returns output in stdout */
void	last_redirect(t_shell *cmd, int i)
{
	dup2(cmd->p_fds[i - 1].fd[0], STDIN_FILENO);
	close(cmd->p_fds[i - 1].fd[0]);
}

/** reads input from the last pipe readind end 
 ** writes output on the writing end of pipe instead of on stdout*/
void	std_redirect(t_shell *cmd, int i)
{
	dup2(cmd->p_fds[i - 1].fd[0], STDIN_FILENO);
	dup2(cmd->p_fds[i].fd[1], STDOUT_FILENO);
	close(cmd->p_fds[i - 1].fd[0]);
	close(cmd->p_fds[i].fd[1]);
}

void	close_fds(t_shell *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->n_inputs - 1)
	{
		close(cmd->p_fds[i].fd[0]);
		close(cmd->p_fds[i].fd[1]);
	}
}

int	wait_for_child(t_shell *cmd)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < cmd->n_inputs)
	{
		waitpid(cmd->pids[i], &wstatus, 0);
	}
	// if (WIFEXITED(wstatus))
	// 	return (WEXITSTATUS(wstatus));
	//return (-1);
	return (0);
}
