/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:12:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/10 16:47:48 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	already_analyzed(char *str)
{
	static int	toret;
	int			sender;

	if (!str && toret > 0)
	{
		sender = toret;
		toret = 0;
		return (sender);
	}
	else if (str)
	{
		toret = ft_strlen(str);
		return (toret);
	}
	else
		return (-1);
}

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
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34 && i < *pos && str[i])
				i++;
		}
		if (str[i] == 39)
			count_sgl++;
		i++;
	}
	if (count_sgl % 2 > 0)
		return (1);
	else
		return (0);
}

char	*addprefix(char *cmd, int *pos, char *toret)
{
	char	*newtoret;

	while (cmd[*pos])
	{
		toret = strjoinchr(toret, cmd[*pos]);
		*pos += 1;
	}
	newtoret = alocpy(toret);
	free(toret);
	return (newtoret);
}

char	*addsufix(char *cmd, int *pos)
{
	char	*toret;
	int		i;

	toret = initalize_str();
	i = already_analyzed(NULL);
	if (i > 0)
	{
		while (cmd[*pos] && *pos < i)
		{
			toret = strjoinchr(toret, cmd[*pos]);
			*pos += 1;
		}
	}
	while (cmd[*pos] && cmd[*pos] != '$')
	{
		toret = strjoinchr(toret, cmd[*pos]);
		*pos += 1;
	}
	if (cmd[*pos] == '$' && check_wrap(cmd, pos))
		toret = wrapped_dollar(cmd, pos, toret);
	return (toret);
}
