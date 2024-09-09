/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:58:54 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 12:55:40 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*savestr;
	char	*lastfound;
	int		found;
	int		i;

	savestr = (char *)s;
	i = 0;
	found = 0;
	if ((char)c == 0)
		return (((char *)s + ft_strlen(s)));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			found = 1;
			lastfound = savestr;
		}
		savestr++;
		i++;
	}
	if (found == 1)
		return (lastfound);
	return (NULL);
}
