/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:35:36 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 11:57:36 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	toin;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	toin = c;
	ptr = s;
	while (i < n)
		ptr[i++] = toin;
	return (s);
}
// #include <stdio.h>
// int main()
// {
// 	char str[] = "Hello World!";
// 	ft_memset(str, 'a', 5);
// 	printf("%s\n", str);
// 	return (0);
// }
