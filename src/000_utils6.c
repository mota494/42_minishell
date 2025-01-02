/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:59:06 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/02 14:28:54 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token *cmds)
{
	int	toret;

	toret = 0;
	if (!cmds)
		return (0);
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

int	count_pipes(t_token *sh)
{
	int		count;
	t_token	*temp;

	temp = sh;
	count = 0;
	while (temp)
	{
		if (sstrcmp(temp->orig_line, "|"))
			count++;
		temp = temp->next;
	}
	return (count + 1);
}

char	*get_doc_file(char *toret)
{
	static char	*filename;

	if (!toret)
		return (filename);
	else
	{
		filename = toret;
		return (toret);
	}
}
