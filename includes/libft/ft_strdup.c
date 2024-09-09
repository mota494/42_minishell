/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:17:53 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/09 10:18:12 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstring;
	size_t	i;
	size_t	strl;

	i = 0;
	strl = ft_strlen(s);
	newstring = ft_calloc(strl + 1, sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[i] != '\0')
	{
		newstring[i] = s[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char string[] = "Teste";
// 	int strl;

// 	strl = strlen(string);
// 	printf("%s\n", ft_strdup(string, strl));
// 	return (0);
// }
