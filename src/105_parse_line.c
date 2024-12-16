/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   105_parse_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:33:48 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/16 17:00:37 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_dbl_quotes(char *oldtoret, char *o_line, int *pos)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	*pos += 1;
	while (o_line[*pos] && o_line[*pos] != 34)
	{
		if (o_line[*pos] == '$')
			newtoret = parse_dollar(o_line, pos, newtoret);
		else
		{
			newtoret = strjoinchr(newtoret, o_line[*pos]);
			*pos += 1;
		}
	}
	*pos += 1;
	return (newtoret);
}

char	*parse_sgl_quotes(char *oldtoret, char *o_line, int *pos)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	*pos += 1;
	while (o_line[*pos] && o_line[*pos] != 39)
	{
		newtoret = strjoinchr(newtoret, o_line[*pos]);
		*pos += 1;
	}
	*pos += 1;
	return (newtoret);
}

char	*parse_line(char *o_line)
{
	char	*newtoret;
	int		i;

	i = 0;
	newtoret = initalize_str();
	while (o_line[i])
	{
		if (o_line[i] == 34)
			newtoret = parse_dbl_quotes(newtoret, o_line, &i);
		else if (o_line[i] == 39)
			newtoret = parse_sgl_quotes(newtoret, o_line, &i);
		else if (o_line[i] == '$')
			newtoret = parse_dollar(o_line, &i, newtoret);
		else
		{
			newtoret = strjoinchr(newtoret, o_line[i]);
			i++;
		}
	}
	return (newtoret);
}
