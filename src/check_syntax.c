/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:48:32 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/09/24 18:12:05 by sofiabueno       ###   ########.fr       */
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
			d_quotes++;
		else if (str[i] == 39)
			s_quotes++;
	}
	if (d_quotes % 2 != 0 || s_quotes % 2 != 0)
	{
		print_error(cmd, ERROR_QUOTE, 2, NULL);
		return (1);
	}
	return (0);
}

void	fix_spaces(char **str)
{
	trim_spaces(str);
	trim_in_between(str);
	return ;
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
			{
				if (check_pipe(cmd, str, i))
					return (1);
			}
			else if (op == '>')
			{
				if (check_redout_apend(cmd, str, i))
					return (1);
			}
			else if (op == '<')
			{
				if (check_redin_heredoc(cmd, str, i))
					return (1);
			}
		}
	}
	return (0);
}

/*checar os codigos de erro*/
int	check_syntax(t_shell *cmd, char *line)
{
	if (check_quotes(cmd, line))
		return (1);
	fix_spaces(&line);
	if (check_operators(cmd, line))
		return (1);
	return (0);
}