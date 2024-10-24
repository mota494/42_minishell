/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/24 14:19:42 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_err(t_shell *cmd)
{
	t_token	*temp;
	int		in_command;

	temp = cmd->token;
	in_command = 0;
	while (temp)
	{
		if (temp->type == error && in_command == 0)
		{
			cmd->error_code = 127;
			in_command = 1;
			printf("%s: command not found\n", temp->cmd_line);
		}
		if (temp->type == control)
			in_command = 0;
		temp = temp->next;
	}
	return (1);
}

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
		temp->orig_line = alocpy(temp->cmd_line);
		remove_quote(temp->cmd_line, temp->quote);
		temp = temp->next;
	}
}

void	parser(char *line, t_shell *cmd)
{
	tokenize(line, cmd);
	quote_removal(cmd->token);
	get_vars(cmd);
	cmd->n_inputs = true_ninput(cmd->token);
	special_case(cmd);
	check_err(cmd);
	get_type(NULL, NULL, "|");
}
