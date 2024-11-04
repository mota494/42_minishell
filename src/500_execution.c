/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:37:03 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/04 10:39:11 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_shell *cmd)
{
	if (sstrcmp(cmd->token->cmd_line, "cd") == 1)
		cd(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "exit") == 1)
		cmd->error_code = exit_main(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "echo") == 1)
		echo_main(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "pwd") == 1)
		pwd(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "env") == 1)
		builtin_env();
}

int	execute_pipeline(t_shell *cmd, char **envp)
{
	int	i;

	i = 0;
	if (cmd->n_builtin == 1 && cmd->n_inputs == 1)
		exec_builtin(cmd);
	while (i < cmd->n_inputs)
	{
	}
	return (0);
}

