/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_redirects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:30:28 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 10:11:28 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	infile_redirect(char *file_name, char *red_type)
{
	int	fd;

	if (sstrcmp(red_type, "<"))
	{
		fd = open(file_name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		fd = open(get_doc_file(NULL), O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	outfile_redirect(char *file_name, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_handler(char **cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (sstrcmp(cmdline[i], "<") || sstrcmp(cmdline[i], "<<"))
		{
			i++;
			infile_redirect(cmdline[i], cmdline[i - 1]);
		}
		else if (sstrcmp(cmdline[i], ">"))
		{
			i++;
			outfile_redirect(cmdline[i], 0);
		}
		else if (sstrcmp(cmdline[i], ">>"))
		{
			i++;
			outfile_redirect(cmdline[i], 1);
		}
		else
			i++;
	}
}

int	size_new_line(t_shell *cmd)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = cmd->token;
	while (temp && temp->type != control)
	{
		if (temp->type != redirect && temp->type != file)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	free_old_cmd(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
