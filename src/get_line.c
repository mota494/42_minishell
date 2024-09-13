/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/13 16:36:50 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_types	get_type(char *cmd)
{
	printf("\n%s\n", cmd);
	return (error);
}
char	*get_cmd(char *line)
{
	char	*toret;
	int		i;

	i = 0;
	toret = ft_calloc(1 ,1);
	if (line[i] == 34)
		toret = adv_dbl_quote(toret, line, &i);
	else if (line[i] == 39)
		toret = adv_sig_quote(toret, line, &i);
	else
		toret = adv_spaces(toret, line, &i);
	line = line + i;
	return (toret);
}

void	treat_line(char *line, t_shell *cmd)
{
	jump_spaces(line);
	cmd->token = add_node(get_cmd(line));
}
