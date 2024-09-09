/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:29:40 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/09 12:28:24 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*toret;
	size_t	strl;

	strl = ft_strlen(s);
	if (start > strl)
		return (ft_strdup(""));
	else if (len + start > strl)
	{
		len = strl - start;
		toret = ft_calloc(len + 1, sizeof(char));
	}
	else
		toret = ft_calloc(len + 1, sizeof(char));
	if (!toret)
		return (NULL);
	ft_strlcpy(toret, s + start, len + 1);
	return (toret);
}

// #include <stdio.h>
// int main()
// {
// 	char *string = "hola";
// 	char *temp = ft_substr(string, 2, 3);
// 	printf("%s\n", temp);

// 	return (0);
// }
