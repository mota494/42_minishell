/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/24 14:44:05 by mloureir         ###   ########.fr       */
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
		free(temp->orig_line);
		free(temp);
	}
	cmd->token = NULL;
}
/**reads command line in a loop, checks for syntax errors
 * and tokenizes it*/

void	read_command(t_shell *cmd, char **envp)
{
	char	*line;

	printf("%s\n", envp[1]);
	while (1 && cmd->leave == false)
	{
		line = readline("minishell: ");
		if (check_syntax(cmd, line) == 1)
		{
			add_history(line);
			parser(line, cmd);
			if (cmd->n_inputs > 0)
			{
				if (execute_pipeline(cmd, envp) == 1)
					fprintf(stderr, "Error executing pipeline\n");
			}
			free(line);
			free_all(cmd);
		}
	}
	if (cmd->error_code > 255)
		cmd->error_code = fix_exit(cmd->error_code);
}

/*initiates the main structure*/
void	init_tshell(t_shell *cmd, char **envp)
{
	char	buffer[PATH_MAX];

	ft_bzero(cmd, sizeof(t_shell));
	cmd->curdir = getcwd(buffer, PATH_MAX);
	copy_envs(cmd, envp);
	init_path_dirs(cmd, envp);
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

int	main(int ac, char **av, char **envp)
{
	t_shell	cmd;

	check_input(ac, av);
	init_tshell(&cmd, envp);
	read_command(&cmd, envp);
	free_env(&cmd);
	return (cmd.error_code);
}
