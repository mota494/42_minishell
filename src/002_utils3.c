/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   002_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:23:27 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/24 14:43:28 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sstrcmp(char *tocomp, char *str)
{
	size_t	i;

	i = 0;
	while (tocomp[i] == str[i] && tocomp[i] && str[i])
		i++;
	if (i == ft_strlen(tocomp) && i == ft_strlen(str))
		return (1);
	return (0);
}

void	del_char(char *str, int to_del)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != to_del)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
}

int	fix_exit(int val)
{
	int	toret;
	int	sup;

	sup = val / 256;
	toret = 256 * sup;
	toret = val - toret;
	return (toret);
}

int	true_ninput(t_token *cmds)
{
	int		toret;
	t_token	*temp;

	temp = cmds;
	toret = 0;
	while (temp)
	{
		if (temp->type == builtin || temp->type == control
			|| temp->type == command)
			toret++;
		temp = temp->next;
	}
	return (toret);
}

int	is_there_pipe(t_token *cmd)
{
	t_token	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->type == control)
			return (1);
		temp = temp->next;
	}
	return (0);
}
