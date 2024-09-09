/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/09 17:58:50 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_command(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell~> ");
		if (ft_strlen(line) > 0)
			add_history(line);
	}
	free(line);
}

void	check_input(int ac, char **av)
{
	if (ac != 1 || av[1])
	{
		printf("Minishell doesn't accept any arguments\n");
		exit (1);
	}
}

int	main(int ac, char **av)
{
	check_input(ac, av);
	read_command();
	return (0);
}
