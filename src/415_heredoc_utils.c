/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:25:28 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/03 16:26:49 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_loop(t_shell *cmd, t_token *temp, int i)
{
	if (cmd->eof)
		free(cmd->eof);
	cmd->eof = ft_strdup(temp->next->cmd_line);
	if (sstrcmp(cmd->eof, temp->next->orig_line) == 0)
		cmd->eof_quotes = true;
	heredoc(cmd, i);
	if (cmd->error_code == 2)
		cmd->doc_leave = true;
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

char	*parser_heredoc(t_shell *cmd, char *str)
{
	char	*newtoret;
	int		i;

	i = 0;
	newtoret = initalize_str();
	while (str[i])
	{
		if (str[i] == '$' && cmd->eof_quotes == false)
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

void	find_heredoc(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	cmd->eof_quotes = false;
	heredoc_son(cmd, temp);
}
