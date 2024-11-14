/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parse_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:05:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/14 11:54:24 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*jump_dbl_quotest(char *oldtoret, char *tojump, size_t *pos)
{
	char	*newtoret;

	*pos += 1;
	newtoret = alocpy(oldtoret);
	free(oldtoret);
	while (tojump[*pos] != 34 && tojump[*pos])
	{
		newtoret = strjoinchr(newtoret, tojump[*pos]);
		*pos += 1;
	}
	*pos += 1;
	return (newtoret);
}

char	*jump_sql_quotes(char *oldtoret, char *tojump, size_t *pos)
{
	char	*newtoret;

	*pos += 1;
	newtoret = alocpy(oldtoret);
	free(oldtoret);
	while (tojump[*pos] != 39 && tojump[*pos])
	{
		newtoret = strjoinchr(newtoret, tojump[*pos]);
		*pos += 1;
	}
	*pos += 1;
	return (newtoret);
}

char	*parse_quotes(char *str)
{
	t_count	c;
	char	*toret;

	start_counters(&c);
	toret = initalize_str();
	while (str[c.j])
	{
		if (str[c.j] == 34)
			toret = jump_dbl_quotest(toret, str, &c.j);
		else if (str[c.j] == 39)
			toret = jump_sql_quotes(toret, str, &c.j);
		else
		{
			toret = strjoinchr(toret, str[c.j]);
			c.j++;
		}
	}
	return (toret);
}
