/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   101_parser_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:08:59 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/17 15:25:22 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sub_tilde(char *old_cmd)
{
	int		i;
	char	*home;
	char	*toret;

	i = 0;
	while (old_cmd[i + 1])
	{
		old_cmd[i] = old_cmd[i + 1];
		i++;
	}
	old_cmd[i] = '\0';
	home = get_env("HOME");
	toret = alocpy(home);
	i = -1;
	while (old_cmd[++i])
		toret = strjoinchr(toret, old_cmd[i]);
	return (toret);
}

void	tilde(t_token *cmd)
{
	if (ft_strlen(cmd->cmd_line) > 1)
	{
		if (cmd->cmd_line[1] == '/')
		{
			cmd->cmd_line = sub_tilde(cmd->cmd_line);
			cmd->expand = true;
		}
		else
			return ;
	}
	else
	{
		cmd->cmd_line = sub_tilde(cmd->cmd_line);
		cmd->expand = true;
	}
	if (!cmd->cmd_line)
		cmd->cmd_line = initalize_str();
}
