/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_redifine_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:45:24 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/30 16:04:33 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_control(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	get_ret_type(t_token *cmd)
{
	if (is_builtin(cmd->cmd_line) == 1)
		cmd->type = builtin;
}

void	red_type(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		if (temp->expand == true)
		{
			get_ret_type(temp);
		}
		temp = temp->next;
	}
}
