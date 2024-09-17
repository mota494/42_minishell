/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:43:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/17 13:46:32 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*adv_dbl_quote(char *oldtoret, char *line, int *pos)
{
	char	*novo_toro;

	novo_toro = alocpy(oldtoret);
	*pos += 1;
	while (line[*pos] != 34 && line[*pos])
	{
		novo_toro = strjoinchr(novo_toro, line[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (novo_toro);
}

char	*adv_sig_quote(char *oldtoret, char *line, int *pos)
{
	char	*novo_toro;

	novo_toro = alocpy(oldtoret);
    *pos += 1;
	while (line[*pos] != 39 && line[*pos])
	{
		novo_toro = strjoinchr(novo_toro, line[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (novo_toro);
}

char	*adv_spaces(char *oldtoret, char *line, int *pos)
{
	char	*novo_toro;

	novo_toro = alocpy(oldtoret);
    while (!ft_iseparator(line[*pos]) && line[*pos])
    {
        novo_toro = strjoinchr(novo_toro, line[*pos]);
		if (line[*pos + 1] == 34 || line[*pos + 1] == 39)
			*pos += 1;
        *pos += 1;
    }
	free(oldtoret);
	return (novo_toro);
}

char	*adv_separator(char *oldtoret, char *line, int *pos)
{
	char	*novo_toro;

	novo_toro = alocpy(oldtoret);
	while (ft_iseparator(line[*pos]) && line[*pos])
	{
		novo_toro = strjoinchr(novo_toro, line[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (novo_toro);
}