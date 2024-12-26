/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_get_replace_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:54:42 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 15:29:49 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_var_value(char *oldtoret, char *var_value)
{
	int		i;
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	if (var_value)
	{
		i = 0;
		while (var_value[i])
		{
			newtoret = strjoinchr(newtoret, var_value[i]);
			i++;
		}
	}
	free(oldtoret);
	return (newtoret);
}

char	*get_replace_var(char *orig, int *pos, char *oldtoret)
{
	char	*var;
	char	*newtoret;
	char	*var_value;

	var = initalize_str();
	*pos += 1;
	while (orig[*pos] && (is_env_char(orig[*pos]) || ft_isdigit(orig[*pos])))
	{
		var = strjoinchr(var, orig[*pos]);
		*pos += 1;
	}
	var_value = get_env(var);
	newtoret = return_var_value(oldtoret, var_value);
	free(var);
	return (newtoret);
}
