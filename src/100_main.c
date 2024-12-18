/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/18 09:36:20 by mloureir         ###   ########.pt       */
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

	setup_signals();
	while (1 && cmd->leave == false)
	{
		cmd->copy_envp = send_env();
		reset_fds(cmd->fds[0], cmd->fds[1]);
		line = readline("minishell: ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
		if (check_syntax(cmd, line) == 1)
		{
			return_error_code(cmd);
			parser(line, cmd);
			if (cmd->n_inputs > 0)
			{
				if (execute_pipeline(cmd, cmd->copy_envp) == 1)
					write(2, "Error executing pipeline\n", 25);
			}
			check_err(cmd);
			free(line);
		}
		free_all(cmd);
	}
}

void	init_tshell(t_shell *cmd, char **envp)
{
	char	buffer[PATH_MAX];

	ft_bzero(cmd, sizeof(t_shell));
	cmd->curdir = alocpy(getcwd(buffer, PATH_MAX));
	copy_envs(cmd, envp);
	init_path_dirs(cmd, envp);
}

void	check_input(int ac, char **av)
{
	if (ac != 1 || av[1])
	{
		printf("Minishell v 0.9.5\n");
		exit (1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	cmd;

	check_input(ac, av);
	init_tshell(&cmd, envp);
	read_command(&cmd);
	if (cmd.error_code > 255)
		cmd.error_code = fix_exit(cmd.error_code);
	free_env(&cmd);
	return (cmd.error_code);
}
