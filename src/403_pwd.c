/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   403_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:41:48 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/22 16:06:30 by mloureir         ###   ########.fr       */
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
	}
	else
		printf("%s\n", curdir);
	return (0);
}
