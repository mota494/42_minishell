/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:09 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:41:35 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(int fd, const char *str, va_list strings, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'd' || str[i] == 'i' || str[i] == 'u')
				ft_printint(fd, str, i, strings);
			if (str[i] == 'c')
				ft_putchar(fd, va_arg(strings, int));
			if (str[i] == '%')
				ft_putchar(fd, '%');
			if (str[i] == 's')
				ft_putstr(fd, va_arg(strings, char *));
			if (str[i] == 'x' || str[i] == 'X')
				ft_hexamain(fd, str, i, strings);
			if (str[i] == 'p')
				ft_printpointer(fd, va_arg(strings, unsigned long));
		}
		else
			write(fd, &str[i], 1);
		i++;
	}
}
