/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_runtime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:43:29 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/25 09:43:31 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_command(t_shell *cmd)
{
	if (sstrcmp(cmd->token->cmd_line, "exit"))
		cmd->error_code = exit_main(cmd);
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
