/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:35:40 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/06 17:31:31 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_line(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && temp->type != control)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**get_command_line(t_shell *cmd)
{
	char	**cmdline;
	t_token	*temp;
	int		i;

	temp = cmd->token;
	cmdline = malloc(sizeof(char *) * (size_line(temp) + 1));
	i = 0;
	while (temp && temp->type != control)
	{
		if (is_redirect(temp->cmd_line) && temp->type == string)
			temp = temp->next;
		else
		{
			cmdline[i] = ft_strdup(temp->cmd_line);
			i++;
			temp = temp->next;
		}
	}
	cmdline[i] = NULL;
	return (cmdline);
}

int	alloc_pids(t_shell *cmd)
{
	cmd->pids = (pid_t *) ft_calloc(cmd->n_inputs, sizeof(pid_t));
	cmd->pids_alloc = 1;
	if (!cmd->pids)
	{
		ft_printf(2, "Memory allocation issue - alloc_pids");
		return (1);
	}
	return (0);
}

int	count_tokens(t_token *current_token)
{
	int	count;

	count = 0;
	while (current_token && sstrcmp(current_token->cmd_line, "|") != 1)
	{
		count++;
		current_token = current_token->next;
	}
	return (count);
}

char	**get_command_tokens(t_token *token)
{
	int		num_token;
	char	**args;
	t_token	*current;
	int		i;

	current = token;
	num_token = count_tokens(current);
	args = malloc(sizeof(char *) * (num_token + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (current && strcmp(current->cmd_line, "|") != 0)
	{
		if (current->type == redirect)
			current = current->next;
		else
		{
			args[i] = alocpy(current->cmd_line);
			current = current->next;
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}
