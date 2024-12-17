/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:00:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/17 16:27:16 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		printf("WOAH");
	else if (sig == SIGQUIT)
		printf("GRRRRR");
}

void	setup_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
