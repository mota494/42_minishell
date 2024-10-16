/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_special.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:39 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/03 10:47:40 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_token *node)
{
	free(node->cmd_line);
	free(node->orig_line);
	free(node);
}

void	check_empty(t_shell *cmd)
{
	t_token	*temp;
	t_token	*prev;

	temp = cmd->token;
	while (temp->next)
	{
		prev = temp;
		temp = temp->next;
		if (ft_strlen(temp->cmd_line) <= 0)
		{
			prev->next = temp->next;
			free_node(temp);
			temp = prev->next;
		}
	}
}

void	check_specials(t_token *cmd)
{
	if (cmd->orig_line[0] == '~')
		tilde(cmd);
	//if (parse_question(cmd->orig_line))
		//dollar_question(cmd);
}

void	special_case(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		check_specials(temp);
		temp = temp->next;
	}
}
