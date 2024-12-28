/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:40:01 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/28 13:19:49 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_fds(t_shell *cmd, int fd_in, int fd_out)
{
	cmd->copy_envp = send_env();
	init_path_dirs(cmd, cmd->copy_envp);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	read_command(t_shell *cmd)
{
	char	*line;

	while (1 && cmd->leave == false)
	{
		reset_fds(cmd, cmd->fds[0], cmd->fds[1]);
		line = readline("minishell: ");
		if (line)
			cmd->line_len = ft_strlen(line);
		if (line && ft_strlen(line) > 0)
			add_history(line);
		if (check_syntax(cmd, line) == 1)
		{
			return_error_code(cmd);
			parser(line, cmd);
			free(line);
			if (ft_strlen(cmd->token->cmd_line) == 0)
			{
				return_last_signal(0);
				free_all(cmd);
				free_for_heredoc(cmd);
				continue ;
			}
			check_err(cmd);
			if (cmd->n_inputs > 0)
				if (execute_pipeline(cmd, cmd->copy_envp) == 1)
					write(2, "Error executing pipeline\n", 25);
			unlink_files(cmd);
		}
		return_last_signal(0);
		free_all(cmd);
		free_for_heredoc(cmd);
	}
}

void	init_tshell(t_shell *cmd, char **envp)
{
	char	buffer[PATH_MAX];

	ft_bzero(cmd, sizeof(t_shell));
	cmd->filename = NULL;
	cmd->curdir = alocpy(getcwd(buffer, PATH_MAX));
	setup_signals(IGNORE);
	copy_envs(cmd, envp);
}

void	check_input(int ac, char **av)
{
	if (ac != 1 || av[1])
	{
		printf("Minishell does not accept any arguments\n");
		exit (1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	cmd;

	if (!envp[0])
		return (0);
	check_input(ac, av);
	init_tshell(&cmd, envp);
	read_command(&cmd);
	if (cmd.error_code > 255)
		cmd.error_code = fix_exit(cmd.error_code);
	free_env(&cmd);
	return (cmd.error_code);
}
