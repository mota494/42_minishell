/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   201_get_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:43:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/24 12:04:19 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	even_quote(char *str, int quote_type)
{
	t_count c;

	start_counters(&c);
	while (str[c.i])
	{
		if (str[c.i] == quote_type)
			c.d++;
		c.i++;
	}
	if (c.d % 2 == 0)
		return (1);
	else
		return (0);
}

char	*adv_dbl_quote(char *oldtoret, char *line, int *pos)
{
	char	*trt;

	trt = alocpy(oldtoret);
	trt = strjoinchr(trt, line[*pos]);
	*pos += 1;
	while (!ft_iseparator(line[*pos]) && line[*pos])
	{
		trt = strjoinchr(trt, line[*pos]);
		*pos += 1;
	}
	while (!even_quote(trt, 34) && line[*pos])
	{
		trt = strjoinchr(trt, line[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (trt);
}

char	*adv_sig_quote(char *oldtoret, char *line, int *pos)
{
	char	*novo_toro;

	novo_toro = alocpy(oldtoret);
	novo_toro = strjoinchr(novo_toro, line[*pos]);
	*pos += 1;
	while (!ft_iseparator(line[*pos]) && line[*pos] != 39 && line[*pos])
	{
		novo_toro = strjoinchr(novo_toro, line[*pos]);
		*pos += 1;
	}
	while (!even_quote(novo_toro, 34) && line[*pos])
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
		if (line[*pos] == 39 || line[*pos] == 34)
		{
			*pos += 1;
			while ((line[*pos] != 39 && line[*pos])
				|| (line[*pos] != 34 && line[*pos]))
			{
				novo_toro = strjoinchr(novo_toro, line[*pos]);
				*pos += 1;
			}
			novo_toro = strjoinchr(novo_toro, line[*pos]);
		}
		else
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
		if (ft_ispace(line[*pos]) == 1)
			break ;
		novo_toro = strjoinchr(novo_toro, line[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (novo_toro);
}
