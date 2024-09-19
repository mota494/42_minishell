/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:36:02 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/09/19 14:59:10 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_shell *cmd, char *error_type, int error_code)
{
	if (error_type != NULL)
	{
		write(2, "minishell: ", 12);
		write(2, error_type, ft_strlen(error_type));
		write(2, "\n", 1);
	}
	cmd->error_code = error_code;
}


// void	syntax_err_msg(t_shell *cmd, char *str, unsigned long i)
// {
// 	if (str[i] == '|')
// 	{
// 		if (str[i + 1] == '|')
// 			print_error(cmd, ERROR_DOUBLE_PIPE, 2);
// 		else if (i == (ft_strlen(str) - 1) && i != 0)
// 			print_error(cmd, ERROR_PIPE_END, 2);
// 		else
// 			print_error(cmd, ERROR_PIPE, 2);
// 	}
// 	else if (str[i] == '<' || str[i] == '>')
// 	{
// 		if (i == 0 || i == ft_strlen(str) - 1)
// 			print_error(cmd, ERROR_REDIRECT, 258);
// 		else if (str[i] == '<')
// 		{
// 			if (str[i + 1] && str[i + 1] == '<')
// 				print_error(cmd, ERR_RED_DOUB_IN, 2);
// 			else
// 				print_error(cmd, ERR_RED_IN, 2);
// 		}
// 		else if (str[i] == '>')
// 		{
// 			if (str[i + 1] && str[i + 1] == '>')
// 				print_error(cmd, ERR_RED_DOUB_OUT, 2);
// 			else
// 				print_error(cmd, ERR_RED_OUT, 2);
// 		}
// 	}
// }
