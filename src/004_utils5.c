/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   004_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:39:22 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/31 10:12:21 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			break ;
		i++;
	}
	return ((int) str[i]);
}

int	f_strcmp(char *tocomp, char *str)
{
	t_count	c;

	start_counters(&c);
	c.j = find_quote_type(str);
	while (str[c.d])
	{
		while (str[c.d] == (char)c.j)
			c.d++;
		if (str[c.d] == tocomp[c.i])
			c.p++;
		else
			return (0);
		c.d++;
		c.i++;
	}
	if (c.p == ft_strlen(tocomp))
		return (1);
	else
		return (0);
}
