/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_parser_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:51 by codespace         #+#    #+#             */
/*   Updated: 2024/12/28 10:54:57 by mloureir         ###   ########.pt       */
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

	while ((line = readline("> ")) != NULL)
	{
		if (sstrcmp(line, cmd->eof))
			break ;
		line = parser_heredoc(line, is_there_quote(cmd->eof));
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	free(line);
	free_all(cmd);
	free_env(cmd);
	exit(cmd->error_code);
}

void	ft_read(t_shell *cmd, int fd)
{
	int		wstatus;

	cmd->heredoc_pid = fork();
	if (cmd->heredoc_pid == 0)
		heredoc_read(cmd, fd);
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
	cmd->filename = get_name(nbr);
	free(nbr);
	fd = open(cmd->filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	get_doc_file(cmd->filename);
	ft_read(cmd, fd);
	close(fd);
	return (fd);
}

void	heredoc_son(t_shell *cmd, t_token *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (sstrcmp(temp->cmd_line, "<<"))
		{
			cmd->eof = ft_strdup(temp->next->cmd_line);
			i++;
			heredoc(cmd, i);
		}
		temp = temp->next;
	}
	cmd->error_code = 0;
}

void	find_heredoc(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	heredoc_son(cmd, temp);
}
