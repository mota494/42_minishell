/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:49:56 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/04 12:06:04 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	c_if_wrap(char *str, int *pos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && i < *pos)
	{
		if (is_quote(str[i]))
			count++;
		i++;
	}
	if (count % 2 > 0)
		return (0);
	return (1);
}

char	*rm_dollar(char *str, int *pos, char *oldtoret)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	*pos += 1;
	while (str[*pos] && str[*pos] != '$')
	{
		newtoret = strjoinchr(newtoret, str[*pos]);
		*pos += 1;
	}
	return (newtoret);
}

char	*not_rm_dollar(char *str, int *pos, char *oldtoret)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	newtoret = strjoinchr(newtoret, str[*pos]);
	*pos += 1;
	while (str[*pos] && str[*pos] != '$')
	{
		newtoret = strjoinchr(newtoret, str[*pos]);
		*pos += 1;
	}
	free(oldtoret);
	return (newtoret);
}

char	*parse_dollar(char *cmd, int *pos, char *oldtoret)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	if (is_quote(cmd[*pos + 1]) && c_if_wrap(cmd, pos))
		newtoret = rm_dollar(cmd, pos, newtoret);
	else if ((is_quote(cmd[*pos + 1]) && !c_if_wrap(cmd, pos)))
		newtoret = not_rm_dollar(cmd, pos, newtoret);
	else if (!is_var_char(cmd[*pos + 1]))
		newtoret = not_rm_dollar(cmd, pos, newtoret);
	else
		newtoret = get_replace_var(cmd, pos, newtoret);
	return (newtoret);
}
