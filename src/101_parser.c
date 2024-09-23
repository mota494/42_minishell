/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/20 16:13:10 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	runtime(t_shell *cmd)
// {
// }

void	remove_quote(char *cmd, t_quotes quote)
{
	if (quote == sgl)
		del_char(cmd, 39);
	else if (quote == dbl)
		del_char(cmd, 34);
}

void	quote_removal(t_token *cmds)
{
	t_token	*temp;

	temp = cmds;
	while (temp)
	{
		remove_quote(temp->cmd_line, temp->quote);
		temp = temp->next;
	}
}

void	parser(char *line, t_shell *cmd)
{
	treat_line(line, cmd);
	quote_removal(cmd->token);
	print_list(cmd);
	// runtime(cmd);
	free_all(cmd);
	free(line);
	get_type("|");
}
