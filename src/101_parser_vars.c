/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/10 09:03:38 by mloureir         ###   ########.fr       */
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

char	*one_var(t_token *cmd, int *pos)
{
	char	*toret;
	char	*helper;

	toret = addsufix(cmd->orig_line, pos);
	helper = alocpy(toret);
	free(toret);
	toret = parse_dollar(cmd->orig_line, pos, helper);
	already_analyzed(toret);
	helper = alocpy(toret);
	free(toret);
	toret = addprefix(cmd->orig_line, pos, helper);
	return (toret);
}

char	*more_vars(char *toret)
{
	char	*helper;
	char	*another_helper;
	int		pos;

	pos = 0;
	helper = alocpy(toret);
	free(toret);
	toret = addsufix(helper, &pos);
	another_helper = alocpy(toret);
	free(toret);
	toret = parse_dollar(helper, &pos, another_helper);
	already_analyzed(toret);
	another_helper = alocpy(toret);
	free(toret);
	toret = addprefix(helper, &pos, another_helper);
	free(helper);
	return (toret);
}

char	*replace_var(t_token *cmd, int var_count)
{
	int		i;
	int		pos;
	char	*toret;

	i = 1;
	pos = 0;
	if (var_count >= 1)
	{
		toret = one_var(cmd, &pos);
		i++;
		while (i++ <= var_count)
			toret = more_vars(toret);
	}
	if (i > 1)
		return (toret);
	else
		return (alocpy(cmd->orig_line));
}

char	*parser_vars(t_token *cmd)
{
	char	*toret;
	int		count_vars;

	count_vars = var_count(cmd->orig_line);
	toret = replace_var(cmd, count_vars);
	return (toret);
}
