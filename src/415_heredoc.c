/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:51 by codespace         #+#    #+#             */
/*   Updated: 2025/01/02 20:49:24 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_read(t_shell *cmd, int fd)
{
	char	*line;

	while (1 && cmd->doc_leave == false)
	{
		line = readline("> ");
		if (sstrcmp(line, cmd->eof) || !line)
			break ;
		line = parser_heredoc(cmd, line);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	free_for_heredoc(cmd);
	free_all(cmd);
	free_env(cmd);
	if (return_last_signal(-1) == SIGINT)
		cmd->error_code = SIGINT;
	exit(cmd->error_code);
}

int	ft_read(t_shell *cmd, int fd)
{
	int		wstatus;

	wstatus = 0;
	setup_signals(TURNOFF);
	cmd->heredoc_pid = fork();
	if (cmd->heredoc_pid == 0)
	{
		heredoc_signals();
		heredoc_read(cmd, fd);
	}
	else
	{
		waitpid(cmd->heredoc_pid, &wstatus, 0);
		ft_printf(2, "%d", wstatus);
		cmd->error_code = wstatus;
		if (wstatus > 255)
			cmd->error_code = WEXITSTATUS(wstatus);
	}
	return (wstatus);
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
			if (sstrcmp(cmd->eof, temp->next->orig_line) == 0)
				cmd->eof_quotes = true;
			heredoc(cmd, i);
			i++;
		}
		temp = temp->next;
	}
	cmd->filename[i] = NULL;
	cmd->error_code = 0;
}
