/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:30:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/31 09:57:16 by mloureir         ###   ########.fr       */
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

char	*strjoinchr(char *oldtoret, char car)
{
	char	*newtoret;
	int		i;

	i = 0;
	newtoret = malloc(ft_strlen(oldtoret) + 2);
	while (oldtoret[i])
	{
		newtoret[i] = oldtoret[i];
		i++;
	}
	newtoret[i] = car;
	newtoret[i + 1] = '\0';
	free(oldtoret);
	return (newtoret);
}
