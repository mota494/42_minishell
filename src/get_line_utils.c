/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:43:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/11 16:55:25 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	adv_dbl_quote(char *oldtoret, char *line, int *pos)
{
	*pos += 1;
	while (line[*pos] != 34 && line[*pos])
	{
		oldtoret = strjoinchr(oldtoret, line[*pos]);
		*pos += 1;
	}
}

void    adv_sig_quote(char *oldtoret, char *line, int *pos)
{
    *pos += 1;
	while (line[*pos] != 39 && line[*pos])
	{
		oldtoret = strjoinchr(oldtoret, line[*pos]);
		*pos += 1;
	}
}

void    adv_spaces(char *oldtoret, char *line, int *pos)
{
    while (ft_ispace(line[*pos]) && line[*pos])
    {
        oldtoret = strjoinchr(oldtoret, line[*pos]);
        *pos += 1;
    }
}