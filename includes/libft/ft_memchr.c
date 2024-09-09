/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:30:41 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 14:55:05 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	chr = (unsigned char) c;
	while (i < n)
	{
		if (str[i] == chr)
			return (str + i);
		i++;
	}
	return (NULL);
}
