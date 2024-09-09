/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:28:12 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/11 12:39:37 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstring;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	newstring = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[i] != '\0')
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	return (newstring);
}
