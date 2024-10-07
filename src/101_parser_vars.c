/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:59:33 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/07 11:59:45 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_var(t_token *cmd)
{
	printf("%s", cmd->cmd_line);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	get_vars(t_shell *cmd)
{
	t_token *temp;

	temp = cmd->token;
	while (temp)
	{
		if (find_dollar(temp->cmd_line) == 1)
		{
			printf("%s", temp->cmd_line);	
		}
		temp = temp->next;
	}
}
