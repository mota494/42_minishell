/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_redirects_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:30:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/27 14:30:49 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	infile_redirect(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	outfile_redirect(char *file_name)
{
	int	fd;

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
		if (sstrcmp(cmdline[i], "<"))
		{
			i++;
			infile_redirect(cmdline[i]);
		}
		else if (sstrcmp(cmdline[i], ">"))
		{
			i++;
			outfile_redirect(cmdline[i]);
		}
		else
			i++;
	}
}

int	size_new_line(char **cmdline)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmdline[i])
	{
		if (sstrcmp(cmdline[i], "<"))
			i = i + 2;
		else if (sstrcmp(cmdline[i], ">"))
			i = i + 2;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
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
