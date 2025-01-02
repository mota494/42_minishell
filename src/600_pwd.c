/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:41:48 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/02 19:23:53 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_pwd_flags(t_token *arg)
{
	if (arg->cmd_line[0] == '-')
	{
		if (arg->cmd_line[1] != '\0')
		{
			ft_printf(2, "minishell: pwd: -%c invalid option\n",
				arg->cmd_line[1]);
			return (0);
		}
	}
	return (1);
}

int	pwd(t_shell *cmd)
{
	char	buffer[PATH_MAX + 1];
	char	*curdir;

	if (!check_for_pwd_flags(cmd->token->next))
	{
		cmd->error_code = 2;
		return (cmd->error_code);
	}
	curdir = getcwd(buffer, PATH_MAX + 1);
	if (!curdir)
	{
		printf("%s\n", cmd->curdir);
		cmd->error_code = 1;
	}
	else
	{
		printf("%s\n", curdir);
		cmd->error_code = 0;
	}
	return (0);
}
