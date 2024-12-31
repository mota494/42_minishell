/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:37:45 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/12/31 16:31:01 by codespace        ###   ########.fr       */
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
		if (str[*i] == '\\' && str[*i + 1])
		{
			(*i)+=2;
			continue ;
		}
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
