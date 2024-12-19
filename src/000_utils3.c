/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:23:27 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 13:46:37 by mloureir         ###   ########.pt       */
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
	char		*var_name;
	t_count		c;
	t_c_envp	*c_envp;

	var_name = initalize_str();
	start_counters(&c);
	c_envp = ret_env(NULL);
	while (str[c.i_i] && str[c.i_i] != '=')
	{
		var_name = strjoinchr(var_name, str[c.i_i]);
		c.i_i++;
	}
	while (c_envp[c.d].var_name)
	{
		if (sstrcmp(c_envp[c.d].var_name, var_name))
			break ;
		c.d++;
	}
	free(var_name);
	if (c.d < size_env(c_envp))
		return (1);
	return (0);
}
