/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:59:16 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:35:50 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(int fd, char *s)
{
	int	i;

	i = 0;
	if (!s)
		write (fd, "(null)", 6);
	else
	{
		while (s[i] != '\0')
		{
			ft_putchar(fd, s[i]);
			i++;
		}
	}
}
