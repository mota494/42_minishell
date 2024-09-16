/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/11 17:44:13 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	jump_spaces(char *line)
{
	while (*line == 32)
		line++;
}

t_types	get_type(char *cmd)
{
	(void)*cmd;
	//printf("%s\n", cmd);
	return (error);
}

char	*strjoinchr(char *str, char c)
{
	char	*newstr;
	size_t	i;

	newstr = malloc(ft_strlen(str) + sizeof(char) + 1);
	i = 0;
	while (i < ft_strlen(str))
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	free(str);
	return (newstr);
}

char	*get_cmd(char *line)
{
	char	*toret;
	int		i;

	i = 0;
	toret = ft_calloc(1 ,1);
	if (line[i] == 34)
	{
		i++;
		while (line[i] != 34 && line[i])
		{
			toret = strjoinchr(toret, line[i]);
			i++;
		}
	}
	else
	{
		while (ft_isspace(line[i]) == 0 && line[i])
		{
			toret = strjoinchr(toret, line[i]);
			i++;
		}
	}
	return (toret);
}

void	treat_line(char *line, t_shell *cmd)
{
	jump_spaces(line);
	cmd->token = add_node(get_cmd(line));
}
