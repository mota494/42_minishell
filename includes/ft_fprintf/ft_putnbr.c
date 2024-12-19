/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:47:37 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:35:25 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int fd, int n)
{
	if (n == -2147483648)
	{
		ft_putchar(fd, '-');
		ft_putchar(fd, '2');
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar(fd, '-');
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(fd, n / 10);
		ft_putnbr(fd, n % 10);
	}
	else
	{
		ft_putchar(fd, n + 48);
	}
}

void	ft_unsputnbr(int fd, unsigned int n)
{
	if (n >= 10)
	{
		ft_putnbr(fd, n / 10);
		ft_putnbr(fd, n % 10);
	}
	else
	{
		ft_putchar(fd, n + 48);
	}
}
