/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:40 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/11 16:19:40 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *tocomp, char *str)
{
	size_t	i;

	i = 0;
	while (tocomp[i] == str[i] && tocomp[i] && str[i])
		i++;
	if (i == ft_strlen(tocomp) && i == ft_strlen(str))
		return (1);
	return (0);
}

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

int	ft_ispace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (ft_strcmp("echo", str))
		return (1);
	else if (ft_strcmp("cd", str))
		return (1);
	else if (ft_strcmp("pwd", str))
		return (1);
	else if (ft_strcmp("export", str))
		return (1);
	else if (ft_strcmp("unset", str))
		return (1);
	else if (ft_strcmp("env", str))
		return (1);
	else if (ft_strcmp("exit", str))
		return (1);
	else
		return (0);
}
