/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_syntax_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:36:02 by sofiabueno        #+#    #+#             */
/*   Updated: 2025/01/02 21:10:08 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_shell *cmd, char *error_type, int error_code, char *compl)
{
	if (error_type != NULL)
	{
		write(2, "minishell: ", 12);
		write(2, error_type, ft_strlen(error_type));
		if (compl)
			write(2, compl, ft_strlen(compl));
		write(2, "\n", 1);
	}
	cmd->error_code = error_code;
}
