/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:51 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 09:41:23 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_read(t_shell *cmd, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = initalize_str();
	while (1 && cmd->doc_leave == false)
	{
		if (fd == -1)
			break ;
		if (i == 0)
			free(line);
		line = readline("> ");
		if (sstrcmp(line, cmd->eof) || !line)
			break ;
		line = parser_heredoc(cmd, line);
		ft_printf(fd, "%s\n", line);
		i++;
		free(line);
	}
	free_loop_heredoc(line, cmd);
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
	int	d;

	d = how_many_heredoc(temp);
	if (d == 0)
		return ;
	cmd->heredoc = true;
	if (!cmd->filename)
		cmd->filename = ft_calloc(sizeof(char *), (d + 1));
	while (temp && temp->type != control)
	{
		if (sstrcmp(temp->cmd_line, "<<"))
		{
			heredoc_loop(cmd, temp, cmd->heredoc_id);
			cmd->heredoc_id++;
		}
		temp = temp->next;
	}
	cmd->filename[cmd->heredoc_id] = NULL;
	cmd->error_code = 0;
}
