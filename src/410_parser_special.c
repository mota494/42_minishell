/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_special.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:39 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/26 13:47:54 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_specials(t_token *cmd)
{
	if (cmd->orig_line[0] == '~')
		tilde(cmd);
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
