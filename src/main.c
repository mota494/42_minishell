/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/17 17:11:22 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *cmd)
{
	t_token *temp;

	if (cmd->token->next)
	{
		while (cmd->token->next)
		{
			temp = cmd->token;
			free(temp->cmd_line);
			free(temp);
			cmd->token = cmd->token->next;
		}
	}
	else if (cmd->token)
	{
		free(cmd->token->cmd_line);
		free(cmd->token);
	}
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
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			treat_line(line, cmd);
			free_all(cmd);
		}
		i++;
	}
	free(line);
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
