/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   301_operators_check2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:05 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/30 16:21:16 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_heredoc(t_shell *cmd, char *str, int i)
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
		else if (is_operator(str[i + 1]))
		{
			if (str [i + 1] == '<' && !str[i + 2])
				return (print_error(cmd, ERROR_REDIRECT, 2, NULL), 1);
			else
				return (check_next_op(cmd, str, i + 1), 1);
		}
	}
	return (0);
}
