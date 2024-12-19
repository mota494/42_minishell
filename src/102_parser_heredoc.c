/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   102_parser_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:51 by codespace         #+#    #+#             */
/*   Updated: 2024/12/19 09:55:06 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
/**go to utils */
/** only takes positive numbers greater than 0 */
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
void	ft_read(t_token *token, int fd)
{
	char	*line;
	printf("fd = %d\n", fd);
	while ((line = readline("> ")) != NULL)
	{
		if (sstrcmp(line, token->eof))
			break ; 
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	free(line);
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
int	heredoc(t_token *token, int i)
{
	char	*filename;
	int		fd;
	filename = get_name(putnbr(i));
	fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	ft_read(token, fd);
	close(fd);
	free(filename);
	return (fd);
}
/*malloc aqui*/
void	find_heredoc(t_shell *cmd)
{
	t_token	*temp;
	int		i;
	temp = cmd->token;
	i = 0;
	while (temp)
	{
		if (sstrcmp(temp->cmd_line, "<<"))
		{
			temp->eof = ft_strdup(temp->next->cmd_line);
			i++;
			heredoc(temp, i);
		}
		temp = temp->next;
	}
}
