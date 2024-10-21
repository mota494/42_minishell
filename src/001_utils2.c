/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:30:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/21 12:13:42 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	jump_spaces(char *line)
{
	int	count_space;
	int	i;

	count_space = 0;
	i = 0;
	while (ft_ispace(line[i]))
	{
		i++;
		count_space++;
	}
	i = 0;
	while (line[i + count_space])
	{
		line[i] = line[i + count_space];
		i++;
	}
	line[i] = '\0';
}

int	ft_ispace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_iseparator(int c)
{
	if ((ft_ispace(c)) == 1)
		return (1);
	else if (c == '|' || c == '&' || c == ';')
		return (1);
	else if (c == '<' || c == '>')
		return (1);
	else if (c == '(' || c == ')')
		return (1);
	return (0);
}

int	scmp(char *tocomp, char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == 34 || str[0] == 39)
	{
		while ((tocomp[i] == str[i + 1] && tocomp[i] && str[i + 1]))
			i++;
		if (i == ft_strlen(tocomp) && i == ft_strlen(str) - 2)
			return (1);
	}
	else
	{
		while (tocomp[i] == str[i] && tocomp[i] && str[i])
			i++;
		if (i == ft_strlen(tocomp) && i == ft_strlen(str))
			return (1);
	}
	return (0);
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
