/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   405_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/22 13:31:54 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(void)
{
	char	**better_env;
	t_c_envp *b_env; 
	int	i;

	i = 0;
	b_env = ret_env(NULL);
	better_env = send_env();
	while (b_env[i].id != -1)
	{
		printf("%s\n", better_env[i]);
		i++;
	}
}
