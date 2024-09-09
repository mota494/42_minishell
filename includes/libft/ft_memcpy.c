/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:06:40 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 10:14:03 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tosrc;
	unsigned char	*todest;
	size_t			i;

	i = 0;
	tosrc = (unsigned char *)src;
	todest = (unsigned char *)dest;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < n && tosrc[i])
	{
		todest[i] = tosrc[i];
		i++;
	}
	return (dest);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char str[] = "1234 5678";
// 	char str2[] = "9012 3456";
// 	char strCPY[] = "1234 5678";
// 	char str2CPY[] = "9012 3456";
// 	ft_memcpy(str, str2, 9);
// 	printf("%s\n", str);
// 	memcpy(strCPY, str2CPY, 9);
// 	printf("%s\n", strCPY);
// 	return (0);
// }
