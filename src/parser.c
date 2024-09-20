/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/19 13:21:27 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quote(char *cmd)
{

}

void	quote_removal(t_token *cmds)
{
	t_token	*temp;

	temp = cmds;
	while (temp)
	{
		remove_quote(temp->cmd_line);
		temp = temp->next;
	}
}

void	parser(char *line, t_shell *cmd)
{
	treat_line(line, cmd);
	print_list(cmd);
	quote_removal(cmd->token);
	//actualy running the commands
	free_all(cmd);
	free(line);
	get_type("|");
}
