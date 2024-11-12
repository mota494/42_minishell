/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/12 14:10:01 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_count(char *str)
{
	t_count	c;

	start_counters(&c);
	while (str[c.d_i])
	{
		if (str[c.d_i] == '$')
		{
			c.d_i++;
			if (ft_isalpha(str[c.d_i])
				|| str[c.d_i] == '?' || str[c.d_i] == '_')
			{
				c.i_i++;
			}
		}
		else
			c.d_i++;
	}
	return (c.i_i);
}

char	*replace_var(t_token *cmd, int var_count, char *toret)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (i < var_count)
	{
		toret = addsufix(cmd->orig_line, &pos);
		toret = parse_dollar(cmd, &pos, toret);
		i++;
	}
	if (i > 0)
		return (toret);
	else
		return (cmd->orig_line);
}

char	*parser_vars(t_token *cmd)
{
	char	*toret;
	int		count_vars;

	toret = initalize_str();
	count_vars = var_count(cmd->orig_line);
	toret = replace_var(cmd, count_vars, toret);
	return (toret);
}
