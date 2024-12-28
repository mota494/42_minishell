/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:37:45 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/12/28 12:59:22 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_quote_closure(char *str, int *i, char quote_type)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			(*i)++;
			if (str[*i] == '\0')
				return (NULL);
		}
		else if (str[*i] == quote_type)
		{
			if (str[*i + 1] == quote_type)
				(*i)++;
			else
				return (&str[*i]);
		}
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
