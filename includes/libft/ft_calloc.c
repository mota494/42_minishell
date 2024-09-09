/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:15:44 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/09 10:17:32 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			sizetotal;
	size_t			i;

	i = 0;
	sizetotal = nmemb * size;
	ptr = (unsigned char *) malloc(sizetotal);
	if (ptr == NULL)
		return (NULL);
	while (i < sizetotal)
		ptr[i++] = 0;
	return (ptr);
}
