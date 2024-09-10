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

void	read_command(t_shell *cmd)
{
	char	*line;

	while (1)
	{
		line = readline("\033[36;1mminishell: \033[0m");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			treat_line(line, cmd);
		}
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

void	init(t_shell *cmd)
{
	cmd->n_inputs = 0;
}

int	main(int ac, char **av)
{
	t_shell	cmd;

	check_input(ac, av);
	init(&cmd);
	read_command(&cmd);
	return (0);
}
