/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/11 16:36:24 by mloureir         ###   ########.fr       */
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

char	*replace_var(t_token *cmd, int var_count)
{
	char	*toret;
	int		i;

	i = 0;
	while (i < var_count)
	{
		toret = addsufix(cmd->cmd_line);
		i++;
	}
	return (toret);
}

char	*parser_vars(t_token *cmd)
{
	char	*toret;
	int		count_vars;

	toret = initalize_str();
	count_vars = var_count(cmd->orig_line);
	toret = replace_var(cmd, count_vars);
	return (cmd->cmd_line);
}
