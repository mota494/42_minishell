/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/31 12:20:49 by mloureir         ###   ########.fr       */
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
		if (temp->type == error && in_command == 0
			&& ft_strlen(temp->cmd_line) > 0)
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

void	remove_quote(t_token *cmd)
{
	if (cmd->quote == sgl)
	{
		del_char(cmd->cmd_line, 39);
		cmd->expand = true;
	}
	else if (cmd->quote == dbl)
	{
		del_char(cmd->cmd_line, 34);
		cmd->expand = true;
	}
}

void	quote_removal(t_token *cmds)
{
	t_token	*temp;

	temp = cmds;
	while (temp)
	{
		temp = temp->next;
	}
}

void	parser(char *line, t_shell *cmd)
{
	tokenize(line, cmd);
	quote_removal(cmd->token);
	get_vars(cmd);
	cmd->n_builtin = count_builtins(cmd->token);
	cmd->n_command = count_command(cmd->token);
	cmd->n_inputs = cmd->n_command + cmd->n_builtin;
	special_case(cmd);
	print_list(cmd);
	check_err(cmd);
	get_type(NULL, NULL, "|");
}
