/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:25:05 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 15:30:22 by mloureir         ###   ########.pt       */
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
		if (temp->type == control)
		{
			temp = temp->next;
			break ;
		}
		temp = temp->next;
	}
	return (temp);
}

char	**only_cmd_arg(t_shell *cmd)
{
	t_token	*temp;
	char	**args;
	int		i;

	temp = cmd->token;
	args = malloc(sizeof(char *) * (size_new_line(cmd) + 1));
	i = 0;
	while (temp && temp->type != control)
	{
		if (temp->type != redirect && temp->type != file)
		{
			args[i] = ft_strdup(temp->cmd_line);
			i++;
		}
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

void	run_final(char **cmdline, char **envp, t_token *sh, t_shell *cmd)
{
	if (!cmdline)
	{
		free_end_exec(cmd);
		exit (1);
	}
	while (sstrcmp(sh->cmd_line, cmdline[0]) == 0)
		sh = sh->next;
	if (ft_strlen(sh->cmd_line) == 0
		|| (sh->type != builtin && sh->type != command))
	{
		cmd->error_code = 127;
		free_end_exec(cmd);
		free_args(cmdline);
	}
	else if (sh->type == builtin)
		execute_builtin(cmd, cmdline);
	else if (sh->type == command)
		execute_command(sh, envp, cmdline);
	else
	{
		free_end_exec(cmd);
		free_args(cmdline);
		cmd->error_code = 127;
	}
	exit (cmd->error_code);
}

void	child_process(t_shell *cmd, char **envp, int help, int i)
{
	int		p[2];
	char	**cmdline;

	pipe(p);
	setup_signals(TURNOFF);
	cmd->pids[i] = fork();
	setup_signals(COMMANDS);
	if (cmd->pids[i] == -1)
		return ;
	if (cmd->pids[i] == 0)
	{
		if (i != 0)
			dup2(help, STDIN_FILENO);
		if (cmd->n_inputs > 1 && i != cmd->n_inputs - 1)
			dup2(p[1], STDOUT_FILENO);
		cmdline = find_command_line(cmd);
		if (cmd->eof)
			free_for_heredoc(cmd);
		close(p[1]);
		close(p[0]);
		run_final(cmdline, envp, cmd->token, cmd);
	}
	dup2(p[0], help);
	close(p[0]);
	close(p[1]);
}

int	execute_pipeline(t_shell *cmd, char **envp, int i)
{
	int		help;
	t_token	*head;

	if (cmd->n_inputs == 1 && cmd->n_builtin == 1)
	{
		find_heredoc(cmd);
		one_builtin(cmd);
		return (0);
	}
	if ((alloc_pids(cmd) != 0))
		return (1);
	help = dup(STDIN_FILENO);
	head = cmd->token;
	while (cmd->token)
	{
		find_heredoc(cmd);
		child_process(cmd, envp, help, i);
		cmd->token = get_next(cmd->token);
		i++;
	}
	cmd->token = head;
	close(help);
	wait_for_child(cmd);
	return (0);
}
