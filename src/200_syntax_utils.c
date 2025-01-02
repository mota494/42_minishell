/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:37:45 by sofiabueno        #+#    #+#             */
/*   Updated: 2025/01/02 15:58:00 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	* find_quote_closure(char *str, int *i, char quote_type)
{
	if (!str[*i + 1])
		return (NULL);
	(*i)++;
	while (str[*i])
	{
		// if (str[*i] == '\\' && str[*i + 1])
		// {
		// 	(*i)+=2;
		// 	continue ;
		// }
		if (str[*i] == quote_type)
			return (&str[*i]);
		(*i)++;
	}
	return (NULL);
}

char	is_operator(char c)
{
	char	*str;

	str = ft_strchr(OPERATORS, c);
	if (!str)
		return (0);
	return (str[0]);
}
