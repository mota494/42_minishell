/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   004_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:39:22 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/25 14:54:44 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(int c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	find_quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			break ;
		i++;
	}
	return ((int) str[i]);
}

size_t	size_env(t_c_envp *b_env)
{
	size_t	i;

	i = 0;
	while (b_env[i].var_name)
		i++;
	return (i);
}
