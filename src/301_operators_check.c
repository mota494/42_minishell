/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:47:22 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/09/23 15:00:29 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/** decidir se vamos tratar open pipes 
 *  Check error values;
*/
int	check_pipe(t_shell *cmd, char *str, int op_index)
{
	int	i;

	i = op_index -1;
	if (i < 0)
	{
		print_error(cmd, ERROR_PIPE, 2, NULL);
		return (1);
	}
	i = op_index + 1;
	if (!str[i])
	{
		print_error(cmd, ERROR_PIPE_END, 2, NULL);
		return (1);
	}
	else if (str[i] == '|')
	{
		print_error(cmd, ERROR_DOUBLE_PIPE, 2, NULL);
		return (1);
	}
	else if ((ft_ispace(str[i]) && str[i + 1] == '|'))
	{
		print_error(cmd, ERROR_PIPE, 2, NULL);
		return (1);
	}
	return (0);
}

int	check_next_op(t_shell *cmd, char *str, int op_index)
{
	if (str[op_index] == '>')
	{
		if (str[op_index + 1] && str[op_index + 1] == '>')
			return (print_error(cmd, ERR_GENERAL, 2, "`>>'"), 1);
		else
			return (print_error(cmd, ERR_GENERAL, 2, "`>'"), 1);
	}
	else if (str[op_index] == '<')
	{
		if (str[op_index + 1] && str[op_index + 1] == '<')
			return (print_error(cmd, ERR_GENERAL, 2, "`<<'"), 1);
		else
			return (print_error(cmd, ERR_GENERAL, 2, "`<'"), 1);
	}
	else if (str[op_index] == '|')
		return (print_error(cmd, ERROR_PIPE, 2, NULL), 1);
	return (0);
}

int	check_append(t_shell *cmd, char *str, int i)
{
	if (!str[i + 1])
	{
		print_error(cmd, ERROR_REDIRECT, 2, NULL);
		return (1);
	}
	else
	{
		if (ft_ispace(str[i + 1]) && str[i + 2] && is_operator(str[i + 2]))
		{
			check_next_op(cmd, str, i + 2);
			return (1);
		}
		else if (ft_ispace(str[i + 1]))
		{
			check_next_op(cmd, str, i + 1);
			return (1);
		}
	}
	return (0);
}

/** checar caso >| verificar se dá erro em check_pipes */
int	check_redout_apend(t_shell *cmd, char *str, int op_index)
{
	int	i;

	i = op_index + 1;
	if (!str[i])
	{
		print_error(cmd, ERROR_REDIRECT, 2, NULL);
		return (1);
	}
	else
	{
		if (is_operator(str[i]))
		{
			if (str[i] == '>')
				return (check_append(cmd, str, i));
			else if (str[i] == '<')
			{
				print_error(cmd, ERR_GENERAL, 2, "`<'");
				return (1);
			}
		}
		else if (ft_ispace(str[i]) && is_operator(str[i + 1]))
			if (check_next_op(cmd, str, i + 1))
				return (1);
	}
	return (0);
}

int	check_redin_heredoc(t_shell *cmd, char *str, int op_index)
{
	int	i;

	i = op_index + 1;
	if (!str[i])
	{
		print_error(cmd, ERROR_REDIRECT, 2, NULL);
		return (1);
	}
	else if (is_operator(str[i]))
	{
		if (str[i] == '<')
			return (check_heredoc(cmd, str, i), 1);
		else if (str[i] == '|')
			return (print_error(cmd, ERROR_PIPE, 2, NULL), 1);
	}
	else if (ft_ispace(str[i]) && is_operator(str[i + 1]))
		return (check_next_op(cmd, str, i + 1), 1);
	return (0);
}
