/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:48:32 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/09/23 14:43:54 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(t_shell *cmd, char *str)
{
	int	d_quotes;
	int	s_quotes;
	int	i;

	d_quotes = 0;
	s_quotes = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
		{
			d_quotes++;
			if (find_quote_closure(str, &i, 34))
				d_quotes++;
		}
		else if (str[i] == 39)
		{
			s_quotes++;
			if (find_quote_closure(str, &i, 39))
				s_quotes++;
		}
	}
	if (d_quotes % 2 != 0 || s_quotes % 2 != 0)
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
					return (1);
		}
	}
	return (1);
}

/*checar os codigos de erro*/
int	check_syntax(t_shell *cmd, char *line)
{
	if (ft_strlen(line) <= 0)
		return (0);
	remove_spaces(line);
	if (!check_quotes(cmd, line))
		return (0);
	if (!check_operators(cmd, line))
		return (0);
	return (1);
}
