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

char	*sub_tilde(char *old_cmd)
{
	int	i;
	char	*home;
	char	*toret;

	i = 0;
	while (old_cmd[i + 1])
	{
		old_cmd[i] = old_cmd[i + 1];
		i++;
	}
	old_cmd[i] = '\0';
	home = getenv("HOME");
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
			cmd->cmd_line = sub_tilde(cmd->cmd_line); 
		else
			return ;
	}
	else
		cmd->cmd_line = sub_tilde(cmd->cmd_line);
}

void	check_specials(t_token *cmd)
{
	if (cmd->cmd_line[0] == '~')
		tilde(cmd);
}

void	special_case(t_shell *cmd)
{
	t_token *temp;

	temp = cmd->token;
	while (temp)
	{
		check_specials(temp);
		temp = temp->next;
	}
}
