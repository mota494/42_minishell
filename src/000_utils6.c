/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:59:06 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/17 12:17:10 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token *cmds)
{
	int	toret;

	toret = 0;
	while (cmds)
	{
		if (cmds->type != string)
			break ;
		cmds = cmds->next;
		toret++;
	}
	return (toret);
}

int	is_var_char(int c)
{
	if (c == '%' || c == '^' || c == '~')
		return (0);
	if (c == '/' || c == ',' || c == '.')
		return (0);
	if (c == ':' || c == 0 || c == '$')
		return (0);
	return (1);
}

int	is_env_char(int c)
{
	if (!ft_isalpha(c) && c != '_')
		return (0);
	return (1);
}

int	return_error_code(t_shell *sh)
{
	static t_shell	*sh_address;

	if (!sh)
		return (sh_address->error_code);
	else
	{
		sh_address = sh;
		return (0);
	}
}
