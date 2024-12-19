/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:25:05 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 15:37:52 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_next(t_token *current)
{
	t_token	*temp;

	if (current == NULL)
		return (NULL);
	temp = current->next;
	while (temp)
	{
		if (temp->type == 4)
		{
			temp = temp->next;
			break ;
		}
		temp = temp->next;
	}
	return (temp);
}

void	child_process(t_shell *cmd, char **envp, int help, int i)
{
	int	p[2];

	pipe(p);
	setup_signals(COMMANDS);
	cmd->pids[i] = fork();
	if (cmd->pids[i] == -1)
		return ;
	if (cmd->pids[i] == 0)
	{
		if (i != 0)
			dup2(help, STDIN_FILENO);
		if (cmd->n_inputs > 1 && i != cmd->n_inputs - 1)
			dup2(p[1], STDOUT_FILENO);
		handle_redirect(cmd->token);
		run_cmdx_builtx(cmd, cmd->token, envp);
		close(p[0]);
		close(p[1]);
		close(help);
	}
	dup2(p[0], help);
	close(p[0]);
	close(p[1]);
}

int	execute_pipeline(t_shell *cmd, char **envp)
{
	int		help;
	int		i;
	t_token	*head;

	if (cmd->n_inputs == 1 && cmd->n_builtin == 1)
	{
		one_builtin(cmd);
		return (0);
	}
	if ((alloc_pids(cmd) != 0))
		return (1);
	i = 0;
	help = dup(STDIN_FILENO);
	head = cmd->token;
	while (cmd->token)
	{
		child_process(cmd, envp, help, i);
		setup_signals(IGNORE);
		cmd->token = get_next(cmd->token);
		i++;
	}
	cmd->token = head;
	close(help);
	wait_for_child(cmd);
	return (0);
}
