/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:38:04 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:57 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pointerputnbr(int fd, unsigned long n, char *hex);
void	ft_hexdefine(int fd, unsigned long n);

void	ft_printpointer(int fd, unsigned long l)
{
	if (!l)
		write(fd, "(nil)", 5);
	else
	{
		write (fd, "0x", 2);
		ft_hexdefine(fd, l);
	}
}

void	ft_hexdefine(int fd, unsigned long n)
{
	ft_pointerputnbr(fd, n, "0123456789abcdef");
}

void	ft_pointerputnbr(int fd, unsigned long n, char *hex)
{
	if (n >= 16)
	{
		ft_pointerputnbr(fd, n / 16, hex);
		ft_pointerputnbr(fd, n % 16, hex);
	}
	else
		ft_putchar(fd, hex[n]);
}
