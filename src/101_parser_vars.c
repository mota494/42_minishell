/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/13 11:32:16 by mloureir         ###   ########.fr       */
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
			c.i_i++;
		}
		else
			c.d_i++;
	}
	return (c.i_i);
}

char	*replace_var(t_token *cmd, int var_count)
{
	int		i;
	int		pos;
	char	*helper;
	char	*toret;

	i = 1;
	pos = 0;
	if (var_count >= 1)
	{
		toret = addsufix(cmd->orig_line, &pos);
		toret = parse_dollar(cmd->orig_line, &pos, toret);
		toret = addprefix(cmd->orig_line, &pos, toret);
		i++;
		while (i++ <= var_count)
		{
			pos = 0;
			helper = alocpy(toret);
			toret = addsufix(helper, &pos);
			toret = parse_dollar(helper, &pos, toret);
			toret = addprefix(helper, &pos, toret);
		}
	}
	if (i > 1)
		return (toret);
	else
		return (cmd->orig_line);
}

char	*parser_vars(t_token *cmd)
{
	char	*toret;
	int	count_vars;

	count_vars = var_count(cmd->orig_line);
	toret = replace_var(cmd, count_vars);
	return (toret);
}
