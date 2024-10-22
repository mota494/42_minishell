/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_runtime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:43:29 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/22 16:04:53 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_builtin(t_shell *cmd)
{
	if (sstrcmp(cmd->token->cmd_line, "exit"))
		cmd->error_code = exit_main(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "echo"))
		echo_main(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "cd"))
		cd(cmd);
	else if (sstrcmp(cmd->token->cmd_line, "pwd"))
		cmd->error_code = pwd(cmd);
	return (1);
}

void	check_command(t_shell *cmd)
{
	if (cmd->token->type != string)
		go_builtin(cmd);
}

void	runtime(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (cmd->token)
	{
		check_command(cmd);
		cmd->token = cmd->token->next;
	}
	cmd->token = temp;
}
