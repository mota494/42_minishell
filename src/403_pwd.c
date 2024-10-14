/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   403_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:41:48 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/14 12:41:51 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	buffer[PATH_MAX + 1];
	char	*curdir;

	curdir = getcwd(buffer, PATH_MAX + 1);
	if (access(curdir, F_OK) == -1)
	{
		printf("pwd: error retrieving current directory: getcwd:"
			"cannot access parent directories: No"
			"such file or directory\n");
			return (1);
	}
	else
		printf("%s\n", curdir);
	return (0);
}
