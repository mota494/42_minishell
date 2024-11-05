/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:37:03 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/05 11:08:21 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_shell *cmd, t_token *curr)
{
	if (sstrcmp(curr->cmd_line, "cd") == 1)
		cd(cmd);
	else if (sstrcmp(curr->cmd_line, "exit") == 1)
		cmd->error_code = exit_main(cmd);
	else if (sstrcmp(curr->cmd_line, "echo") == 1)
		echo_main(cmd);
	else if (sstrcmp(curr->cmd_line, "pwd") == 1)
		pwd(cmd);
	else if (sstrcmp(curr->cmd_line, "env") == 1)
		builtin_env();
}

void	go_to_next(t_token *cmd)
{
	if (cmd->next)
	{
		*cmd = *(cmd)->next;
		while (cmd->type != builtin && cmd->type != command)
			*cmd = *(cmd)->next;
	}
}

void	redirect_first(int *fd)
{
	dup2(fd[1], 1);
	close(fd[0]);
}

void	redirect_last(int *fd)
{
	dup2(fd[0], 0);
	close(fd[1]);
}

void	redirect_mid(int *fd)
{
	dup2(fd[1], fd[0]);
}

void	redirection(int *fd, int pos, int ninputs)
{
	if (pos == 1)
		redirect_first(fd);
	else if (pos == ninputs)
		redirect_last(fd);
	else
		redirect_mid(fd);
}

void	execution(t_shell *cmd, t_token *temp, char **envp, int pos)
{
	int	fd[2];
	pid_t	child;

	printf("[%s]", envp[1]);
	pipe(fd);	
	child = fork();
	if (child == 0)
	{
		redirection(fd, pos, cmd->n_inputs);
		if (temp->type == builtin)
			exec_builtin(cmd, temp);
	}
	else
	{
		wait(NULL);
	}
}

int	execute_pipeline(t_shell *cmd, char **envp)
{
	int		i;
	t_token	*temp;

	i = 1;
	printf("%s\n", envp[1]);
	temp = cmd->token;
	if (cmd->n_builtin == 1 && cmd->n_inputs == 1)
	{
		exec_builtin(cmd, temp);
		i++;
	}
	while (i <= cmd->n_inputs)
	{
		execution(cmd, temp, envp, i);
		go_to_next(temp);
		i++;
	}
	return (cmd->error_code);
}
