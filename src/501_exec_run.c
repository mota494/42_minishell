/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   501_exec_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:46:10 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/20 15:16:17 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_builtin(char **args, t_shell *cmd)
{
	if (!args || !args[0])
		return ;
	if (sstrcmp(args[0], "cd") == 1)
		cd(cmd);
	else if (sstrcmp(args[0], "exit") == 1)
		cmd->error_code = exit_main(cmd);
	else if (sstrcmp(args[0], "echo") == 1)
		echo_main(cmd);
	else if (sstrcmp(args[0], "pwd") == 1)
		pwd(cmd);
	else if (sstrcmp(args[0], "env") == 1)
		builtin_env(cmd);
}

int	one_builtin(t_shell *cmd)
{
	t_token	*current_token;
	char	**args;

	current_token = cmd->token;
	if (current_token->type == builtin)
	{
		args = get_command_tokens(current_token);
		while (current_token)
		{
			if (current_token->type == pipes)
				return (1);
			current_token = current_token->next;
		}
		call_builtin(args, cmd);
		free_args(args);
		return (0);
	}
	return (1);
}

int	execute_builtin(t_shell *cmd, t_token *token)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_command_tokens(current_token);
	call_builtin(args, cmd);
	free_args(args);
	return (0);
}

int	execute_command(t_token *token, char **envp)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_command_tokens(current_token);
	if (execve(current_token->path_name, args, envp) == -1)
	{
		perror("execve");
		return (1);
	}
	free(args);
	return (0);
}

void	run_cmdx_builtx(t_shell *cmd, t_token *current, char **envp)
{
	if (current && current->type == builtin)
		execute_builtin(cmd, current);
	else if (current && current->type == command)
		execute_command(current, envp);
	exit(0);
}
