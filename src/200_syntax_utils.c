/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:07:43 by sbueno-s          #+#    #+#             */
/*   Updated: 2025/01/02 21:07:57 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_quote_closure(char *str, int *i, char quote_type)
{
	if (!str[*i + 1])
		return (NULL);
	(*i)++;
	while (str[*i])
	{
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
