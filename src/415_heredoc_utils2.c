/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_heredoc_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:41:11 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/06 16:55:07 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_eof(char *str)
{
	char	*toret;
	t_count	c;

	start_counters(&c);
	toret = initalize_str();
	while (str[c.i_i])
	{
		if (str[c.i_i] == 34 || str[c.i_i] == 39)
		{
			c.d_i = str[c.i_i];
			c.i_i++;
			while (str[c.i_i] && str[c.i_i] != c.d_i)
			{
				toret = strjoinchr(toret, str[c.i_i]);
				c.i_i++;
			}
			c.i_i++;
		}
		else
		{
			toret = strjoinchr(toret, str[c.i_i]);
			c.i_i++;
		}
	}
	return (toret);
}

int	is_there_quote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
