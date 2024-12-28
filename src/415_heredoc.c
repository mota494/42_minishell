/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_parser_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:51 by codespace         #+#    #+#             */
/*   Updated: 2024/12/28 13:44:39 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_read(t_shell *cmd, int fd)
{
	char	*line;

	while ((line = readline("> ")))
	{
		if (sstrcmp(line, cmd->eof) || !line)
			break ;
		line = parser_heredoc(line, is_there_quote(cmd->eof));
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	free(line);
	free_for_heredoc(cmd);
	free_all(cmd);
	free_env(cmd);
	exit(cmd->error_code);
}

void	ft_read(t_shell *cmd, int fd)
{
	int		wstatus;

	cmd->heredoc_pid = fork();
	if (cmd->heredoc_pid == 0)
	{
		heredoc_signals();
		heredoc_read(cmd, fd);
	}
	else
	{
		waitpid(cmd->heredoc_pid, &wstatus, 0);
		if (wstatus > 255)
			cmd->error_code = WEXITSTATUS(wstatus);
	}
}

int	heredoc(t_shell *cmd, int i)
{
	int		fd;
	char	*nbr;

	nbr = putnbr(i);
	cmd->filename[i] = get_name(nbr);
	free(nbr);
	fd = open(cmd->filename[i], O_CREAT | O_TRUNC | O_RDWR, 0644);
	get_doc_file(cmd->filename[i]);
	ft_read(cmd, fd);
	close(fd);
	return (fd);
}

int	how_many_heredoc(t_token *temp)
{
	int		i;
	t_token	*a_temp;

	i = 0;
	a_temp = temp;
	while (a_temp)
	{
		if (sstrcmp(a_temp->cmd_line, "<<"))
			i++;
		a_temp = a_temp->next;
	}
	return (i);
}

void	heredoc_son(t_shell *cmd, t_token *temp)
{
	int	i;
	int	d;

	i = 0;
	d = how_many_heredoc(temp);
	if (d == 0)
		return ;
	cmd->heredoc = true;
	cmd->filename = ft_calloc(sizeof(char *), (d + 1));
	while (temp)
	{
		if (sstrcmp(temp->cmd_line, "<<"))
		{
			if (cmd->eof)
				free(cmd->eof);
			cmd->eof = ft_strdup(temp->next->cmd_line);
			heredoc(cmd, i);
			i++;
		}
		temp = temp->next;
	}
	cmd->filename[i] = NULL;
	cmd->error_code = 0;
}
