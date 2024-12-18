/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:00:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/18 15:12:50 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_last_signal(int n_signal)
{
	static int	l_signal;

	if (n_signal != -1)
		l_signal = n_signal;
	return (l_signal);
}

void	handle_quit(int sig)
{
	return_last_signal(sig);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(int mode)
{
	if (mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == COMMANDS)
	{
		signal(SIGQUIT, handle_quit);
	}
}
