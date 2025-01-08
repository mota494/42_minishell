/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution_run.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:46:10 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 10:10:43 by mloureir         ###   ########.pt       */
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
		exit_main(cmd);
	else if (sstrcmp(args[0], "echo") == 1)
		echo_main(cmd);
	else if (sstrcmp(args[0], "pwd") == 1)
		pwd(cmd);
	else if (sstrcmp(args[0], "env") == 1)
		builtin_env(cmd);
	else if (sstrcmp(args[0], "export"))
		export_main(cmd);
	else if (sstrcmp(args[0], "unset"))
		unset_env(cmd);
}

int	one_builtin(t_shell *cmd)
{
	t_token	*current_token;
	char	**args;

	current_token = cmd->token;
	while (current_token && current_token->type != builtin)
		current_token = current_token->next;
	if (current_token->type == builtin)
	{
		args = get_command_line(cmd);
		one_redirect_handler(args);
		free_args(args);
		args = only_cmd_arg(cmd);
		call_builtin(args, cmd);
		free_args(args);
		return (0);
	}
	return (1);
}

int	execute_builtin(t_shell *cmd, char **args)
{
	call_builtin(args, cmd);
	free_args(args);
	free_all(cmd);
	free_env(cmd);
	exit(cmd->error_code);
	return (cmd->error_code);
}

int	execute_command(t_token *token, char **envp, char **args)
{
	t_token	*current_token;

	current_token = token;
	token->type = command;
	if (execve(current_token->path_name, args, envp) == -1)
		return (1);
	free(args);
	return (0);
}
