/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/11 09:47:22 by mloureir         ###   ########.fr       */
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

void	get_redirect_type(t_token *sh)
{
	t_types	last_type;
	t_token	*temp;

	temp = sh;
	last_type = temp->type;
	temp = temp->next;
	while (temp)
	{
		if (last_type == redirect)
			temp->type = file;
		last_type = temp->type;
		temp = temp->next;
	}
}

void	parser(char *line, t_shell *cmd)
{
	tokenize(line, cmd);
	cmd->n_builtin = count_builtins(cmd->token);
	cmd->n_command = count_command(cmd->token);
	cmd->n_inputs = cmd->n_command + cmd->n_builtin;
	special_case(cmd);
	get_redirect_type(cmd->token);
	get_type(NULL, NULL, "|", "|");
	already_analyzed(NULL);
}
