/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:34:09 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 14:28:55 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(int fd, const char *str, ...);
void	ft_flags(int fd, const char *str, va_list strings, int i);
void	ft_printint(int fd, const char *str, int strpos, va_list strings);
void	ft_putnbr(int fd, int n);
void	ft_putchar(int fd, char c);
void	ft_putstr(int fd, char *s);
void	ft_hexamain(int fd, const char *str, int strpos, va_list strings);
void	ft_unsputnbr(int fd, unsigned int n);
void	ft_printpointer(int fd, unsigned long l);

#endif
