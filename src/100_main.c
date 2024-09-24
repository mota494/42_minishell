/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/19 10:02:34 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *cmd)
{
	t_token	*temp;

	while (cmd->token)
	{
		temp = cmd->token;
		cmd->token = cmd->token->next;
		free(temp->cmd_line);
		free(temp);
	}
	cmd->token = NULL;
}

void	read_command(t_shell *cmd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 3)
	{
		cmd->n_inputs = 0;
		line = readline("minishell: ");
		if (check_syntax(cmd, line) == 1)
		{
			add_history(line);
			parser(line, cmd);
		}
		i++;
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
