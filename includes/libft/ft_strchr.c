/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:06:35 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 11:59:11 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*savestr;
	char	check;
	int		i;

	savestr = (char *)s;
	i = 0;
	check = c;
	if (check == 0)
		return (((char *)s + ft_strlen(s)));
	while (s[i] != '\0')
	{
		check = c;
		if (s[i] == check)
			return (savestr);
		savestr++;
		i++;
	}
	return (NULL);
}
