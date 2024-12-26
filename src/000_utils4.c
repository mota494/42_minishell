/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:12:56 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/23 15:32:11 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_counters(t_count *counters)
{
	counters->d = 0;
	counters->i = 0;
	counters->j = 0;
	counters->p = 0;
	counters->i_i = 0;
	counters->d_i = 0;
	counters->j_i = 0;
}

char	*initalize_str(void)
{
	char	*newstr;

	newstr = malloc(1);
	newstr[0] = '\0';
	return (newstr);
}

int	count_builtins(t_token *cmd)
{
	t_token	*temp;
	int		toret;

	temp = cmd;
	toret = 0;
	while (temp)
	{
		if (temp->type == builtin)
			toret++;
		temp = temp->next;
	}
	return (toret);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_var_name(char *str)
{
	int	i;

	i = 0;
	if (!is_env_char(str[i]))
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
