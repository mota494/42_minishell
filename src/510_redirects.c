/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:37:54 by codespace         #+#    #+#             */
/*   Updated: 2025/01/03 14:25:53 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_tokens(t_token *token)
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

void	check_red(char **args)
{
	int		i;
	char	*red;

	i = -1;
	red = NULL;
	while (args[++i])
	{
		if (is_redirect(args[i]) == 1)
			red = ft_strdup(args[i]);
	}
	if (red == NULL)
		return ;
	else
	{
		free (red);
	}
}
