/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   305_define_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:15:44 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/11 17:04:26 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (sstrcmp("echo", str))
		return (1);
	else if (sstrcmp("cd", str))
		return (1);
	else if (sstrcmp("pwd", str))
		return (1);
	else if (sstrcmp("export", str))
		return (1);
	else if (sstrcmp("unset", str))
		return (1);
	else if (sstrcmp("env", str))
		return (1);
	else if (sstrcmp("exit", str))
		return (1);
	return (0);
}

int	is_controler(char *str)
{
	if (sstrcmp("\n", str))
		return (1);
	if (sstrcmp("|", str) || sstrcmp("||", str))
		return (1);
	return (0);
}

int	is_redirect(char *str)
{
	if (sstrcmp("<<", str) || sstrcmp(">>", str))
		return (1);
	if (sstrcmp(">|", str))
		return (1);
	if (sstrcmp("<", str) || sstrcmp(">", str))
		return (1);
	if (sstrcmp("<&", str) || sstrcmp("<>", str) || sstrcmp(">&", str))
		return (1);
	return (0);
}

int	is_var(char *str)
{
	if (str[0] == '$' && str[1] == 0)
		return (0);
	else if (str[0] == '$' && !ft_iseparator(str[1]))
		return (1);
	else if (str[0] == 34 && str[1] == '$')
		return (1);
	return (0);
}

/*malloc em strdup liberar path_name no fim*/
int	is_command(t_shell *cmd, t_token *new_node, char *str)
{
	if (find_slash(str) && (access(str, X_OK) == 0))
	{
		new_node->path_name = ft_strdup(str);
		new_node->got_path = true;
		return (1);
	}
	else if (find_absolute_path(cmd, new_node, str))
		return (1);
	return (0);
}
