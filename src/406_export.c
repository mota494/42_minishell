/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   406_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:41:02 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/02 11:10:55 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_export_args(t_token *cmd)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = cmd->next;
	while (temp && temp->type == string)
	{
		if (var_exist(temp->cmd_line) == 0)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	check_export_args(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	if (!temp->next || temp->next->type != string)
	{
		print_export();
		cmd->error_code = 0;
		return (1);
	}
	else
	{
		export_new(count_export_args(temp), temp, cmd);
		return (1);
	}
	return (0);
}

void	export_main(t_shell *cmd)
{
	if (check_export_args(cmd))
		return ;
}
