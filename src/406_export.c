/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   406_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:41:02 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/25 14:24:10 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (0);
}

void	export_main(t_shell *cmd)
{
	if (check_export_args(cmd))
		return ;
}
