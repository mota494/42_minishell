/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:30:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/16 15:53:48 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	jump_spaces(char *line)
{
	while (*line == 32 && *line != '\0')
		line++;
}

int	ft_ispace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	scmp(char *tocomp, char *str)
{
	size_t	i;

	i = 0;
	if (tocomp[0] == 34 || tocomp[0] == 39)
	{
	i += 1;
	while ((tocomp[i] == str[i] && tocomp[i] && str[i]))
		i++;
	if (i == ft_strlen(tocomp) - 1 && i == ft_strlen(str))
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