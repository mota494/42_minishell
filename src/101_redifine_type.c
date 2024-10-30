/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_redifine_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:45:24 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/30 09:47:33 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	red_type(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		if (temp->expand == true)
		{
			printf("[%s]", temp->cmd_line);
		}
		temp = temp->next;
	}
}
