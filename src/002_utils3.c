/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   002_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:23:27 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/02 10:52:07 by mloureir         ###   ########.fr       */
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

int	var_exist(char *str)
{
	char	*var_name;
	int		i;

	var_name = initalize_str();
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var_name = strjoinchr(var_name, str[i]);
		i++;
	}
	if (get_env(var_name))
		return (1);
	free(var_name);
	return (0);
}
