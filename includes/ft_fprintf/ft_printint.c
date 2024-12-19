/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:52 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:32:12 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printint(int fd, const char *str, int strpos, va_list strings)
{
	int					num;
	unsigned long		unslong;

	if (str[strpos] == 'i' || str[strpos] == 'd')
	{
		num = va_arg(strings, int);
		ft_putnbr(fd, num);
	}
	else
	{
		unslong = va_arg(strings, unsigned int);
		ft_unsputnbr(fd, unslong);
	}
}
