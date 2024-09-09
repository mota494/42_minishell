/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:35:44 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/04 14:46:49 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_reversememcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tosrc;
	unsigned char	*todest;

	tosrc = (unsigned char *)src;
	todest = (unsigned char *)dest;
	while (n-- > 0)
		todest[n] = tosrc[n];
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		ft_reversememcpy(dest, src, n);
	else if (dest < src)
		ft_memcpy(dest, src, n);
	else
		return (dest);
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
// 	ft_memmove(str, str2, 3);
// 	printf("%s\n", str);
// 	memmove(strCPY, str2CPY, 3);
// 	printf("%s\n", strCPY);
// 	return (0);
// }
