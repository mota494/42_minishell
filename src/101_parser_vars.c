/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/24 14:27:29 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char *str, int *helper)
{
	int		i;
	char	*toret;

	i = 0;
	toret = malloc(1);
	toret[0] = '\0';
	while (str[i] != '$')
		i++;
	i++;
	while ((ft_isalpha(str[i]) == 1 || str[i] == '_') && str[i])
	{
		toret = strjoinchr(toret, str[i]);
		i++;
	}
	if (str[i] != '\0')
		*helper = 0;
	return (toret);
}

int	check_for_expand(t_token *cmd)
{
	t_count	c;

	start_counters(&c);
	while (cmd->orig_line[c.i] != '$' && cmd->orig_line[c.i] != '\0')
		c.i++;
	if (ft_isalpha(cmd->orig_line[c.i + 1]) || cmd->orig_line[c.i + 1] == '_')
		return (1);
	return (0);
}

int	find_quote_pos(t_token *cmd)
{
	t_count	c;

	start_counters(&c);
	if (check_for_expand(cmd) == 0)
		return (0);
	while (cmd->orig_line[c.i] && cmd->orig_line[c.i] != '$')
	{
		if (cmd->orig_line[c.i] == 39)
			c.d++;
		c.i++;
	}
	if (find_dollar(cmd->orig_line) == 0)
		return (0);
	else if (find_dollar(cmd->orig_line) && c.d == 1
		&& cmd->quote == sgl)
		return (0);
	else if (find_dollar(cmd->orig_line) && c.d == 1)
		return (0);
	else if (find_dollar(cmd->orig_line) && c.d == 2)
		return (1);
	else
		return (1);
}

char	*replace_var(char *var_name, t_token *cmd)
{
	char	*toret;
	int		pos;

	pos = 0;
	toret = get_prefix(cmd->cmd_line, &pos);
	toret = get_var_val(toret, cmd, var_name, &pos);
	toret = get_suffix(toret, cmd->cmd_line, &pos);
	return (toret);
}

void	get_vars(t_shell *cmd)
{
	t_token	*temp;
	char	*var_name;
	int		helper;

	temp = cmd->token;
	while (temp)
	{
		helper = find_quote_pos(temp);
		if (helper == 1)
		{
			var_name = find_var(temp->orig_line, &helper);
			temp->cmd_line = replace_var(var_name, temp);
			temp->expanded = true;
			free(var_name);
		}
		temp = temp->next;
	}
}
