/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_check_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:48:32 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/12/23 14:14:53 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(t_shell *cmd, char *str)
{
	t_count	c;

	start_counters(&c);
	c.i_i = -1;
	while (str[++c.i_i])
	{
		if (str[c.i_i] == 34)
		{
			c.d_i++;
			if (find_quote_closure(str, &c.i_i, 34))
				c.d_i++;
		}
		else if (str[c.i_i] == 39)
		{
			c.j_i++;
			if (find_quote_closure(str, &c.i_i, 39))
				c.j_i++;
		}
	}
	if (c.d_i % 2 != 0 || c.j_i % 2 != 0)
	{
		print_error(cmd, ERROR_QUOTE, 2, NULL);
		return (0);
	}
	return (1);
}

void	remove_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return ;
	while (ft_ispace(str[i]) == 1)
		i++;
	if (i > 0)
	{
		while (str[j + i])
		{
			str[j] = str[j + i];
			j++;
		}
		str[j] = '\0';
	}
	i = ft_strlen(str);
	while (ft_ispace(str[i - 1]) == 1)
		i--;
	str[i] = '\0';
}

int	check_operators(t_shell *cmd, char *str)
{
	int		i;
	char	op;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			find_quote_closure(str, &i, str[i]);
		else
		{
			op = is_operator(str[i]);
			if (op == '|')
				if (check_pipe(cmd, str, i))
					return (0);
			if (op == '>')
				if (check_redout_apend(cmd, str, i))
					return (0);
			if (op == '<')
				if (check_redin_heredoc(cmd, str, i))
					return (0);
		}
	}
	return (1);
}

/*checar os codigos de erro*/
/* if any syntax error is found it returns 0
** else, it returns 1 and parcing continues
 */
int	check_syntax(t_shell *cmd, char *line)
{
	if (!line)
	{
		write(2, "exit\n", 5);
		cmd->leave = true;
		return (0);
	}
	if (ft_strlen(line) <= 0)
		return (0);
	remove_spaces(line);
	if (!check_quotes(cmd, line))
		return (0);
	if (!check_operators(cmd, line))
		return (0);
	return (1);
}
