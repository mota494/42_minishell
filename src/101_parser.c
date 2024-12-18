/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/18 16:45:52 by codespace        ###   ########.fr       */
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

void	parser(char *line, t_shell *cmd)
{
	tokenize(line, cmd);
	cmd->n_builtin = count_builtins(cmd->token);
	cmd->n_command = count_command(cmd->token);
	cmd->n_inputs = cmd->n_command + cmd->n_builtin;
	special_case(cmd);
	//check_err(cmd);
	get_type(NULL, NULL, "|", "|");
	//print_list(cmd);
	already_analyzed(NULL);
	find_heredoc(cmd);
}
