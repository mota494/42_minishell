/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/30 16:06:48 by sofiabueno       ###   ########.fr       */
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

	while (1)
	{
		line = readline("minishell: ");
		if (check_syntax(cmd, line) == 1)
		{
			add_history(line);
			parser(line, cmd);
			if (cmd->leave == true)
				break ;
		}
	}
	if (cmd->error_code > 255)
		cmd->error_code = fix_exit(cmd->error_code);
}

/*initiates the main structure*/
void	init_tshell(t_shell *cmd)
{
	cmd->leave = false;
	cmd->n_inputs = 0;
	cmd->error_code = 0;
	ft_bzero(cmd, sizeof(t_shell));
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

int	main(int ac, char **av)
{
	t_shell	cmd;

	check_input(ac, av);
	init_tshell(&cmd);
	read_command(&cmd);
	return (cmd.error_code);
}
