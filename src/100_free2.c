/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:05:01 by sbueno-s          #+#    #+#             */
/*   Updated: 2025/01/02 21:05:43 by sbueno-s         ###   ########.fr       */
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
