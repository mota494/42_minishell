/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:47:22 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/09/19 15:34:45 by sofiabueno       ###   ########.fr       */
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
		print_error(cmd, ERROR_PIPE, 2);
		return (1);
	}
	i = op_index + 1;
	if (!str[i])
	{
		print_error(cmd, ERROR_PIPE_END, 2);
		return (1);
	}
	else if (str[i] == '|')
	{
		print_error(cmd, ERROR_DOUBLE_PIPE, 2);
		return (1);
	}
	else if ((ft_isspace(str[i]) && str[i + 1] == '|'))
	{
		print_error(cmd, ERROR_PIPE, 2);
		return (1);
	}
	return (0);
}
