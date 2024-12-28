/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_parser_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:51 by codespace         #+#    #+#             */
/*   Updated: 2024/12/28 13:06:38 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*get_doc_file(char *toret)
{
	static char *filename;

	if (!toret)
		return (filename);
	else
	{
		filename = toret;
		return (toret);		
	}
}

char	*putnbr(int i)
{
	int		nbr;
	int		len;
	char	*str;
	nbr = i;
	len = 0;
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	nbr = i;
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

int	is_there_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

char	*parser_heredoc(char *str, int mode)
{
	char	*newtoret;
	int		i;

	i = 0;
	newtoret = initalize_str();
	while (str[i])
	{
		if (str[i] == '$' && mode == 0)
			newtoret = parse_dollar(str, &i, newtoret, 0);
		else
		{
			newtoret = strjoinchr(newtoret, str[i]);
			i++;
		}
	}
	free(str);
	return (newtoret);	
}

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

void	heredoc_sighandle(int signo)
{
	if (signo == SIGQUIT)
	{
		return_last_signal(signo);
	}
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, heredoc_sighandle);	
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
char	*get_name(char *char_nb)
{
	char	*template;
	char	*filename;
	char	*temp;

	template = "heredoc_temp_";
	temp = ft_strjoin(template, char_nb);
	filename = ft_strjoin(temp, ".txt");
	free(temp);
	return (filename);
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
	t_token *a_temp;

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

void	find_heredoc(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	heredoc_son(cmd, temp);
}
