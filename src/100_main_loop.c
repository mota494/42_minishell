/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:16:09 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/11 15:12:42 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_exec(t_shell *cmd, char *line)
{
	if (return_last_signal(-1) == SIGINT)
		cmd->error_code = 130;
	return_error_code(cmd);
	parser(line, cmd);
	free(line);
	if (ft_strlen(cmd->token->cmd_line) == 0 && cmd->n_inputs == 0)
	{
		cmd->error_code = 0;
		return ;
	}
	if (cmd->n_inputs > 0)
		if (execute_pipeline(cmd, cmd->copy_envp, 0) == 1)
			write(2, "Error executing pipeline\n", 25);
	check_err(cmd);
	if (cmd->heredoc == true)
		unlink_files(cmd);
}

int	check_if_only_spaces(char *str)
{
	t_count	c;

	start_counters(&c);
	while (str[c.i_i])
	{
		if (ft_ispace(str[c.i_i]))
			c.d_i++;
		c.i_i++;
	}
	if (c.d_i == c.i_i)
		return (1);
	else
		return (0);
}

void	minishell_loop(t_shell *cmd, char *line)
{
	reset_fds(cmd, cmd->fds[0], cmd->fds[1]);
	line = readline("minishell: ");
	if (line)
		cmd->line_len = ft_strlen(line);
	if (line && ft_strlen(line) > 0 && check_if_only_spaces(line) != 1)
		add_history(line);
	if (check_syntax(cmd, line) == 1)
	{
		minishell_exec(cmd, line);
	}
}
