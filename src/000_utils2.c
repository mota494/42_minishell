/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:30:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/31 09:57:16 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	jump_spaces(char *line)
{
	int	count_space;
	int	i;

	count_space = 0;
	i = 0;
	while (ft_ispace(line[i]))
	{
		i++;
		count_space++;
	}
	i = 0;
	while (line[i + count_space])
	{
		line[i] = line[i + count_space];
		i++;
	}
	line[i] = '\0';
}

int	ft_ispace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	scmp(char *tocomp, char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == 34 || str[0] == 39)
	{
		while ((tocomp[i] == str[i + 1] && tocomp[i] && str[i + 1]))
			i++;
		if (i == ft_strlen(tocomp) && i == ft_strlen(str) - 2)
			return (1);
	}
	else
	{
		while (tocomp[i] == str[i] && tocomp[i] && str[i])
			i++;
		if (i == ft_strlen(tocomp) && i == ft_strlen(str))
			return (1);
	}
	return (0);
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
