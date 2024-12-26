/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   403_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:41:48 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/20 15:05:55 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_shell *cmd)
{
	char	buffer[PATH_MAX + 1];
	char	*curdir;

	curdir = getcwd(buffer, PATH_MAX + 1);
	if (access(curdir, X_OK) == -1)
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
