/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:12:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/13 11:48:31 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*wrapped_dollar(char *str, int *pos, char *newtoret)
{
	newtoret = strjoinchr(newtoret, str[*pos]);
	*pos += 1;
	while (str[*pos] && str[*pos] != '$')
	{
		newtoret = strjoinchr(newtoret, str[*pos]);
		*pos += 1;
	}
	return (newtoret);
}

int	check_wrap(char *str, int *pos)
{
	int	i;
	int	count_sgl;

	i = 0;
	count_sgl = 0;
	while (str[i] && i < *pos)
	{
		if (str[i] == 39)
			count_sgl++;
		i++;
	}
	if (count_sgl % 2 > 0)
		return (1);
	else
		return (0);
}

char	*addprefix(char *cmd, int *pos, char *oldtoret)
{
	while (cmd[*pos])
	{
		oldtoret = strjoinchr(oldtoret, cmd[*pos]);
		*pos += 1;
	}
	return (oldtoret);
}

char	*addsufix(char *cmd, int *pos)
{
	char	*toret;

	toret = initalize_str();
	while (cmd[*pos] && cmd[*pos] != '$')
	{
		toret = strjoinchr(toret, cmd[*pos]);
		*pos += 1;
	}
	if (cmd[*pos] == '$' && check_wrap(cmd, pos))
		toret = wrapped_dollar(cmd, pos, toret);
	return (toret);
}
