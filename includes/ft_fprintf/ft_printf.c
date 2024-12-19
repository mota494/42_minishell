/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:28:31 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:29:21 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *str, ...)
{
	va_list	strings;
	int		count;

	count = 0;
	va_start(strings, str);
	ft_flags(fd, str, strings, 0);
	va_end(strings);
	return (count);
}

//int main()
//{
//	int d;
//	int *ptrD;
//
//	ptrD = &d;
//	d = ft_printf("%p \n\n", -1);
//	ft_printf("%d", d);
//	return (0);
//}
