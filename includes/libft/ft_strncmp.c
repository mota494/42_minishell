/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:48:10 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/06 15:15:06 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *s1 = "\200";
// 	char *s2 = "\0";

// 	printf("%d\n", ft_strncmp(s1, s2, 6));
// 	printf("%d", strncmp(s1, s2, 6));
// }
