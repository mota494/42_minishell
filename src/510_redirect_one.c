/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_redirect_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:35:46 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/28 10:38:11 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_redirect_handler(char **cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (sstrcmp(cmdline[i], ">"))
		{
			i++;
			outfile_redirect(cmdline[i], 0);
		}
		else if (sstrcmp(cmdline[i], ">>"))
		{
			i++;
			outfile_redirect(cmdline[i], 1);
		}
		else
			i++;
	}
}
