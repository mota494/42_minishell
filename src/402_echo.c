/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   402_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:58:43 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/25 13:58:45 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_token *cmd)
{
	int	count_print;
	int	is_n;

	count_print = 0;
	is_n = 0;
	while (cmd)
	{
		if (cmd->type != string)
			break ;
		if (sstrcmp(cmd->cmd_line, "-n") && count_print == 0)
			is_n = 1;
		else
			printf("%s ", cmd->cmd_line);
		count_print++;
		cmd = cmd->next;
	}
	if (is_n == 0)
		printf("\n");
}

void	echo_main(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	temp = temp->next;
	//if (is_there_pipe(temp))
		//send args to pipe
	print_echo(temp);
}
