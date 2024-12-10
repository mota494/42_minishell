/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:12:56 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/10 16:21:30 by mloureir         ###   ########.fr       */
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
		if (temp->type == builtin || temp->type == error)
			toret++;
		temp = temp->next;
	}
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
