/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/09 15:40:01 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>

int main()
{
	char	*test;

	while (1)
	{
		test = readline(" \033[1;34mminishell~> ");
		if (ft_strlen(test) > 0)
			add_history(test);
		printf("%d", history_base);
	}
	free(test);
	return (0);
}
