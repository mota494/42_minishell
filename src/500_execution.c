/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:25:05 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/27 15:11:53 by mloureir         ###   ########.pt       */
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

char	**only_cmd_arg(char **cmdline)
{
	int		i;
	int		y;
	char	**new_cmd_line;

	new_cmd_line = malloc(sizeof(char *) * (size_new_line(cmdline) + 1));
	i = 0;
	y = 0;
	while (cmdline[i])
	{
		if (sstrcmp(cmdline[i], "<"))
			i = i + 2;
		else if (sstrcmp(cmdline[i], ">"))
			i = i + 2;
		else
		{
			new_cmd_line[y] = ft_strdup(cmdline[i]);
			y++;
			i++;
		}
	}
	new_cmd_line[y] = NULL;
	free_old_cmd(cmdline);
	return (new_cmd_line);
}

void	run_final(char **cmdline, char **envp, t_token *token, t_shell *cmd)
{
	while (sstrcmp(token->cmd_line, cmdline[0]) == 0)
		token = token->next;
	if (ft_strlen(token->cmd_line) == 0)
	{
		free_all(cmd);
		free_env(cmd);
		free_args(cmdline);
	}
	else if (token->type == builtin)
		execute_builtin(cmd, cmdline);
	else if (token->type == command)
		execute_command(token, envp, cmdline);
	else
	{
		free_all(cmd);
		free_env(cmd);
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
		cmdline = get_command_line(cmd);
		redirect_handler(cmdline);
		cmdline = only_cmd_arg(cmdline);
		run_final(cmdline, envp, cmd->token, cmd);
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
		cmd->token = get_next(cmd->token);
		i++;
	}
	cmd->token = head;
	close(help);
	wait_for_child(cmd);
	return (0);
}
