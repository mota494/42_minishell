/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_get_line_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:36:13 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/05 09:58:12 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*jump_quotes(char *oldtoret, char *line, int *pos, int quote)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	newtoret = strjoinchr(newtoret, line[*pos]);
	*pos += 1;
	while (line[*pos] && line[*pos] != quote)
	{
		newtoret = strjoinchr(newtoret, line[*pos]);
		*pos += 1;
	}
	if (line[*pos] == quote)
	{
		newtoret = strjoinchr(newtoret, line[*pos]);
		*pos += 1;
	}
	return (newtoret);
}

char	*get_token(char *oldtoret, char *line, int *pos)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	while (line[*pos] && !ft_iseparator(line[*pos]))
	{
		if (is_quote(line[*pos]))
			newtoret = jump_quotes(newtoret, line, pos, line[*pos]);
		else
		{
			newtoret = strjoinchr(newtoret, line[*pos]);
			*pos += 1;
		}
	}
	return (newtoret);
}
