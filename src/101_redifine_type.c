/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_redifine_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:45:24 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/30 11:34:23 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_types	get_ret_type(t_token *cmd)
{
	return (cmd->type);
}

void	red_type(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		if (temp->expand == true)
		{
			temp->type = get_ret_type(temp);
		}
		temp = temp->next;
	}
}
