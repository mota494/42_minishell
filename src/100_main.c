/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/10 16:30:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_fds(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	read_command(t_shell *cmd)
{
	char	*line;

	while (1 && cmd->leave == false)
	{
		cmd->copy_envp = send_env();
		reset_fds(cmd->fds[0], cmd->fds[1]);
		line = readline("minishell: ");
		add_history(line);
		if (check_syntax(cmd, line) == 1)
		{
			parser(line, cmd);
			if (cmd->n_inputs > 0)
			{
				if (execute_pipeline(cmd, cmd->copy_envp) == 1)
					write(2, "Error executing pipeline\n", 25);
			}
			free(line);
			free_all(cmd);
		}
	}
	if (cmd->error_code > 255)
		cmd->error_code = fix_exit(cmd->error_code);
}

void	init_tshell(t_shell *cmd, char **envp)
{
	char	buffer[PATH_MAX];

	ft_bzero(cmd, sizeof(t_shell));
	cmd->curdir = getcwd(buffer, PATH_MAX);
	copy_envs(cmd, envp);
	init_path_dirs(cmd, envp);
}

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
	read_command(&cmd);
	free_env(&cmd);
	return (cmd.error_code);
}
