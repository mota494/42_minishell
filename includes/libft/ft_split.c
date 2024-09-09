/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:32:33 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/11 12:38:36 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int	count;
	int	i;
	int	check;

	count = 0;
	i = 0;
	check = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && check == 0)
		{
			check = 1;
			count++;
		}
		else if (s[i] == c && check == 1)
			check = 0;
		i++;
	}
	return (count);
}

static size_t	wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static char	**strclean(char **split, size_t wordc)
{
	size_t	i;

	i = 0;
	while (i < wordc)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

static char	**writestr(char const *s, char c, char **split, size_t wordc)
{
	size_t	count;
	int		i;
	int		j;

	i = 0;
	count = 0;
	while (count < wordc)
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		split[count] = ft_calloc(wordlen(&s[i], c) + 1, sizeof(char));
		if (!split[count])
			return (strclean(split, wordc));
		while (s[i] != c && s[i])
		{
			split[count][j] = s[i];
			j++;
			i++;
		}
		count++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	wordc;

	wordc = wordcount(s, c);
	split = ft_calloc(wordc + 1, sizeof(char *));
	if (!split)
		return (0);
	if (wordc > 0)
		split = writestr(s, c, split, wordc);
	return (split);
}

/*#include <stdio.h>

int main()
{
    char    *string = "Eu x sou o x teste x";
    char    c = "x";
    char    **newstring;

    newstring = ft_split(string, c);
    printf("%s", newstring[0]);
    printf("%s", newstring[1]);
    printf("%s", newstring[2]);
    return (0);
}*/