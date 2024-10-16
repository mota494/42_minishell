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
	if (access(curdir, X_OK) == -1)
	{
		curdir = getenv("PWD");
		printf("%s\n", curdir);
	}
	else
		printf("%s\n", curdir);
	return (0);
}
