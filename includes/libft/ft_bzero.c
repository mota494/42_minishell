/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:35:55 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/04 11:08:22 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = 0;
}
// #include <stdio.h>
// int main()
// {
// 	char str[] = "Hello World!";
// 	ft_bzero(str, 5);
// 	printf("%s\n", str);
// 	return (0);
// }
