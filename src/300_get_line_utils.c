/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_get_line_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:36:13 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/05 10:28:28 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*adv_separator(char *oldtoret, char *line, int *pos)
{
	char	*novo_toro;

	novo_toro = alocpy(oldtoret);
	while (ft_iseparator(line[*pos]) && line[*pos])
	{
		if (ft_ispace(line[*pos]) == 1)
			break ;
		novo_toro = strjoinchr(novo_toro, line[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (novo_toro);
}

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
