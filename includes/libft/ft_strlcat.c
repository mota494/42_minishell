/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:16:55 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 10:23:45 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	strl[2];
	size_t	i;
	size_t	f;

	i = 0;
	f = 0;
	strl[0] = ft_strlen(dst);
	strl[1] = ft_strlen(src);
	while (dst[i] != '\0')
		i++;
	while (src[f] != '\0' && i < size - 1 && size > 0)
	{
		dst[i] = src[f];
		f++;
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	if (size < strl[0])
		return (size + strl[1]);
	else
		return (strl[0] + strl[1]);
}
/*#include <stdio.h>
#include <bsd/string.h>

int main()
{
	char src[] = "Mota";
	char dest[] = "guel";
	int size = 6;
	char src1[] = "Mota";
	char dest1[] = "guel";
	int size1 = 6;
	printf("Retorno da minha: [%d]\n", ft_strlcat(dest,src,size));
	printf("Retorno strlcat: [%zu]\n", strlcat(dest1, src1, size1));
	printf("Dest da minha: %s\n", dest);
	printf("Dest strlcat: %s", dest1);
}*/
