/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/19 16:01:24 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_command(t_shell *cmd)
{
	char	*line;

	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			if (checksyntax(cmd, line) == 1)
				continue ;
			treat_line(line, cmd);
		}
		free(line);
	}
}

/*checks if the program receives any input*/
void	check_input(int ac, char **av)
{
	if (ac != 1 || av[1])
	{
		printf("Minishell doesn't accept any arguments\n");
		exit (1);
	}
}

/*initiates the main structure*/
void	init(t_shell *cmd)
{
	ft_bzero(cmd, sizeof(t_shell));
}

int	main(int ac, char **av)
{
	t_shell	cmd;

	check_input(ac, av);
	init(&cmd);
	read_command(&cmd);
	return (0);
}
