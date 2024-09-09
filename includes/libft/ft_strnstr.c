/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:25:42 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/09 16:31:55 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		n = 0;
		while ((big[i + n] == little[n]) && big[i + n] != '\0' && i + n < len)
		{
			if (little[n + 1] == '\0')
				return ((char *)&big[i]);
			n++;
		}
		i++;
	}
	return (0);
}
