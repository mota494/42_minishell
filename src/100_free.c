/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:37:46 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/03 17:31:12 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_copy_envp(t_shell *cmd)
{
	int	i;

	i = 0;
	while (cmd->copy_envp[i])
	{
		free(cmd->copy_envp[i]);
		i++;
	}
	free(cmd->copy_envp);
}

void	free_dirs(t_shell *cmd)
{
	int	i;

	i = 0;
	while (cmd->path_dirs[i])
	{
		free(cmd->path_dirs[i]);
		i++;
	}
	free(cmd->path_dirs);
}

void	free_all(t_shell *cmd)
{
	t_token	*temp;

	cmd->token = cmd->head;
	while (cmd->token)
	{
		temp = cmd->token;
		cmd->token = cmd->token->next;
		free(temp->cmd_line);
		free(temp->orig_line);
		if (temp->got_path == true)
			free(temp->path_name);
		free(temp);
	}
	cmd->head = NULL;
	free_pids(cmd);
	cmd->line_len = 0;
	cmd->token = NULL;
	if (cmd->path_dirs)
		free_dirs(cmd);
	free_copy_envp(cmd);
}

void	free_env(t_shell *cmd)
{
	t_count		c;
	t_c_envp	*b_env;

	b_env = ret_env(NULL);
	start_counters(&c);
	while (b_env[c.i].var_name)
	{
		free(b_env[c.i].var_name);
		free(b_env[c.i].var_value);
		c.i++;
	}
	free(cmd->c_envp);
	free(cmd->curdir);
}

void	free_pids(t_shell *cmd)
{
	if (cmd->line_len <= 0)
		return ;
	if (return_last_signal(-1) == SIGQUIT)
		return ;
	if (cmd->pids_alloc == 1)
	{
		free(cmd->pids);
		cmd->pids_alloc = 0;
	}
}
