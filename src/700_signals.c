/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:00:01 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/03 15:46:12 by mloureir         ###   ########.pt       */
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

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		return_last_signal(sig);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig == SIGINT)
	{
		return_last_signal(sig);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_test(int signo)
{
	return_last_signal(signo);
	printf("\n");
	rl_on_new_line();
}

void	setup_signals(int mode)
{
	if (mode == IGNORE)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == COMMANDS)
	{
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_test);
	}
	else if (mode == TURNOFF)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
