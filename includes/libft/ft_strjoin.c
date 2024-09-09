/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:57:07 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/09 11:32:47 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstring;
	size_t	strlen[2];
	size_t	i;

	strlen[0] = ft_strlen(s1);
	strlen[1] = ft_strlen(s2);
	i = 0;
	if (*s1 == '\0' && *s2 == '\0')
		return (ft_strdup(""));
	newstring = ft_calloc(strlen[0] + strlen[1] + 1, sizeof(char));
	if (!newstring)
		return (NULL);
	while (i < strlen[0])
	{
		newstring[i] = s1[i];
		i++;
	}
	while (i < strlen[0] + strlen[1])
	{
		newstring[i] = s2[i - strlen[0]];
		i++;
	}
	return (newstring);
}

// #include <stdio.h>
// int main()
// {
// 	char *string1 = "abcd";
// 	char *string2 = "efghi";
// 	char *temp = ft_strjoin(string1, string2);
// 	printf("%s\n", temp);
// 	return (0);
// }
