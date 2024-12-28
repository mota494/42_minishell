/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:23:27 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/28 15:57:13 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sstrcmp(char *tocomp, char *str)
{
	size_t	i;

	i = 0;
	if (!tocomp || !str)
		return (1);
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

int	count_command(t_token *cmd)
{
	t_token	*temp;
	int		toret;

	temp = cmd;
	toret = 0;
	while (temp)
	{
		if (temp->type == command)
			toret++;
		temp = temp->next;
	}
	return (toret);
}

int	ft_iseparator(int c)
{
	if ((ft_ispace(c)) == 1)
		return (1);
	else if (c == '|' || c == '&' || c == ';')
		return (1);
	else if (c == '<' || c == '>')
		return (1);
	else if (c == '(' || c == ')')
		return (1);
	return (0);
}
