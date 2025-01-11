/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   305_define_type_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:28:48 by sofiabueno        #+#    #+#             */
/*   Updated: 2025/01/11 17:14:57 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

char	*concatenate(char *dir, char *str)
{
	char	*temp;
	char	*path_name;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		printf("join failed");
	path_name = ft_strjoin(temp, str);
	free(temp);
	if (!path_name)
		printf("join failed");
	return (path_name);
}

int	find_absolute_path(t_shell *cmd, t_token *new_node, char *str)
{
	int		i;
	char	*path_tmp;

	path_tmp = NULL;
	i = -1;
	if (!cmd->path_dirs)
		return (0);
	while (cmd->path_dirs[++i])
	{
		path_tmp = concatenate(cmd->path_dirs[i], str);
		if (access(path_tmp, X_OK) == 0)
		{
			if (new_node->got_path == true)
				free(new_node->path_name);
			new_node->got_path = true;
			new_node->path_name = ft_strdup(path_tmp);
			free(path_tmp);
			return (1);
		}
		free(path_tmp);
	}
	return (0);
}
