/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:19:16 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 10:42:30 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_for_heredoc(t_shell *cmd)
{
	if (cmd->filename)
	{
		free_args(cmd->filename);
		cmd->filename = NULL;
	}
	if (cmd->eof)
	{
		free(cmd->eof);
		cmd->eof = NULL;
	}
}

void	unlink_files(t_shell *cmd)
{
	int	i;

	i = 0;
	if (!cmd->filename)
		return ;
	while (cmd->filename[i])
	{
		unlink(cmd->filename[i]);
		i++;
	}
}
