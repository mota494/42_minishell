/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   501_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:35:40 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/11 11:17:19 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	alloc_pids(t_shell *cmd)
{
	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * cmd->n_inputs);
	if (!cmd->pids)
	{
		perror("Memory allocation issue - alloc_pids");
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
		args[i] = alocpy(current->cmd_line);
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}