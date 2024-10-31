/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   303_syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:37:45 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/10/31 15:08:38 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_in_between(char **str)
{
	int		i;
	char	*str_trim;

	str_trim = ft_calloc(1, 1);
	i = 0;
	while ((*str)[i])
	{
		if (ft_ispace((*str)[i]) && (*str)[i + 1] && ft_ispace((*str)[i + 1]))
		{
			while (ft_ispace((*str)[i + 1]))
				i++;
		}
		str_trim = strjoinchr(str_trim, (*str)[i]);
		i++;
	}
	if (str_trim && str_trim != *str)
	{
		free(*str);
		*str = str_trim;
	}
}

void	trim_spaces(char **str)
{
	char	*str_trim;

	if (!str || !*str)
		return ;
	str_trim = ft_strtrim(*str, " \t");
	if (str_trim && str_trim != *str)
	{
		free(*str);
		*str = str_trim;
	}
}

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
