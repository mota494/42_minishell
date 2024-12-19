/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:10:00 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:31:42 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_uphex(int fd, unsigned int num);
void	ft_lowhex(int fd, unsigned int num);
void	ft_putnbrhex(int fd, unsigned int num, char *hex);

void	ft_hexamain(int fd, const char *str, int strpos, va_list strings)
{
	if (str[strpos] == 'x')
		ft_lowhex(fd, va_arg(strings, unsigned int));
	else if (str[strpos] == 'X')
		ft_uphex(fd, va_arg(strings, unsigned int));
}

void	ft_putnbrhex(int fd, unsigned int num, char *hex)
{
	if (num >= 16)
	{
		ft_putnbrhex(fd, num / 16, hex);
		ft_putnbrhex(fd, num % 16, hex);
	}
	else
		ft_putchar(fd, hex[num]);
}

void	ft_uphex(int fd, unsigned int num)
{
	ft_putnbrhex(fd, num, "0123456789ABCDEF");
}

void	ft_lowhex(int fd, unsigned int num)
{
	ft_putnbrhex(fd, num, "0123456789abcdef");
}
