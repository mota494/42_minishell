/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_vars_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:49:56 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/12 14:17:25 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_dollar(t_token *cmd, int *pos, char *oldtoret)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	while (cmd->orig_line[*pos])
		*pos += 1;
	return (newtoret);
}
