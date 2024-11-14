/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_get_replace_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:54:42 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/14 11:07:21 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_replaced(char *oldtoret, char *var_name)
{
	free(oldtoret);
	free(var_name);
}

char	*get_replace_var(char *orig_line, int *pos, char *oldtoret)
{
	char	*var;
	char	*var_value;
	int		i;
	char	*newtoret;

	var = initalize_str();
	*pos += 1;
	newtoret = alocpy(oldtoret);
	while (orig_line[*pos] && (orig_line[*pos] == '_' || ft_isalpha(orig_line[*pos])))
	{
		var = strjoinchr(var, orig_line[*pos]);
		*pos += 1;
	}
	var_value = get_env(var);
	if (var_value)
	{
		i = 0;
		while (var_value[i])
		{
			newtoret = strjoinchr(newtoret, var_value[i]);
			i++;
		}
	}
	free_replaced(oldtoret, var);
	return (newtoret);
}
