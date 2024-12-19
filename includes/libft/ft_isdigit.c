/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:16:30 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 15:24:36 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
// #include <stdio.h>
// int main()
// {
// 	char c = '9';
// 	printf("%d\n", ft_isdigit(c));
// 	return (0);
// }
