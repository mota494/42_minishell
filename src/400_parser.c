/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:01:28 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/11 11:13:51 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_err(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		if (temp->type == error && ft_strlen(temp->cmd_line) > 0)
			printf("%s: command not found\n", temp->cmd_line);
		if (temp->type == folder && ft_strlen(temp->cmd_line) > 0)
			printf("minishell: %s: is a directory\n", temp->cmd_line);
		if ((sstrcmp(temp->orig_line, "\"\"")
				|| sstrcmp(temp->orig_line, "\'\'")) && temp->type != file)
		{
			cmd->error_code = 127;
			printf("%s: command not found\n", temp->orig_line);
		}
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

void	get_folder_type(t_token *sh)
{
	struct stat	buffer;
	t_token		*temp;

	temp = sh;
	while (temp)
	{
		if (!stat(temp->cmd_line, &buffer) && temp->type != string
			&& temp->type != file)
		{
			if (S_ISREG(buffer.st_mode) == 0)
				temp->type = folder;
		}
		temp = temp->next;
	}
}

void	parser(char *line, t_shell *cmd)
{
	cmd->line_len = ft_strlen(line);
	tokenize(line, cmd);
	get_type(NULL, NULL, "|", "|");
	get_redirect_type(cmd->token);
	get_folder_type(cmd->token);
	cmd->n_builtin = count_builtins(cmd->token);
	cmd->n_command = count_command(cmd->token);
	cmd->n_inputs = count_pipes(cmd->token);
}
