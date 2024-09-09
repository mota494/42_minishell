/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:43:41 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 12:39:25 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (i < (size - 1) && src[i] != '\0' && len != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
// #include <stdio.h>
// int main()
// {
// 	char src[10] = "";
// 	char dst[0];
// 	printf("%zu\n", ft_strlcpy(dst, src, 9));
// 	printf("%s\n", dst);
// 	return (0);
// }
