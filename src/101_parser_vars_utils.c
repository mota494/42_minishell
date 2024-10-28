/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:12:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/28 15:53:59 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_wrap_quote(char *str)
{
	t_count	c;

	start_counters(&c);
	while (str[c.i])
	{
		if (str[c.i] == 34 || str[c.i] == 39)
			c.d++;
		if (str[c.i] == '$')
			break ;
		c.i++;
	}
	if (c.d % 2 == 0)
		return (1);
	return (0);
}

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
