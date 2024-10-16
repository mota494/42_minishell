/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:12:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/14 10:20:07 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_prefix(char *str, int *pos)
{
	char	*toret;

	toret = malloc(1);
	toret[0] = '\0';
	while (str[*pos] != '$')
	{
		toret = strjoinchr(toret, str[*pos]);
		*pos += 1;
	}
	*pos += 1;
	return (toret);
}

char	*get_var_val(char *toret, t_token *cmd, char *str, int *pos)
{
	int		i;
	char	*var;

	*pos = *pos + ft_strlen(str);
	var = get_env(str);
	if (!var)
	{
		cmd->type = string;
		return (toret);
	}
	i = 0;
	while (var[i])
	{
		toret = strjoinchr(toret, var[i]);
		i++;
	}
	return (toret);
}

char	*get_suffix(char *toret, char *str, int *pos)
{
	while (str[*pos])
	{
		toret = strjoinchr(toret, str[*pos]);
		*pos += 1;
	}
	return (toret);
}
