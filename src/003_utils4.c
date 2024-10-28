/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   003_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:12:56 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/28 14:45:36 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_counters(t_count *counters)
{
	counters->d = 0;
	counters->i = 0;
	counters->j = 0;
	counters->p = 0;
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
	t_token *temp;
	int	toret;

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

int	count_command(t_token *cmd)
{
	t_token *temp;
	int	toret;

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
