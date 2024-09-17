/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:40 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/17 09:56:49 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*alocpy(char *str)
{
	char	*toret;
	int		i;

	toret = malloc(ft_strlen(str) * sizeof(char) + 1);
	i = 0;
	while (str[i])
	{
		toret[i] = str[i];
		i++;
	}
	toret[i] = '\0';
	return (toret);
}

t_token	*add_node(char	*content)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node->cmd_line = alocpy(content);
	new_node->next = NULL;
	new_node->type = get_type(new_node->cmd_line);
	return (new_node);
}

int	is_builtin(char *str)
{
	if (scmp("echo", str))
		return (1);
	else if (scmp("cd", str))
		return (1);
	else if (scmp("pwd", str))
		return (1);
	else if (scmp("export", str))
		return (1);
	else if (scmp("unset", str))
		return (1);
	else if (scmp("env", str))
		return (1);
	else if (scmp("exit", str))
		return (1);
	else
		return (0);
}
