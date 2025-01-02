/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   415_heredoc_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:57:51 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/02 15:32:00 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sighandle(int signo)
{
	if (signo == SIGINT)
	{
		close(STDIN_FILENO);
		return_last_signal(signo);
	}
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_sighandle);
	signal(SIGQUIT, SIG_IGN);
}

t_shell	*get_struct(t_shell *cmd)
{
	static t_shell	*toret;

	if (cmd)
		toret = cmd;
	return (toret);
}

void	update_leave(void)
{
	t_shell	*cmd;

	cmd = get_struct(NULL);
	cmd->doc_leave = true;
}
