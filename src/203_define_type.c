/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   203_define_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:15:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/02 08:30:51 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (scmp("echo", str))
		return (1);
	else if (scmp("cd", str))
		return (1);
	else if (scmp("pwd", str))
		return (1);
	else if (scmp("export", str))
		return (1);
	else if (scmp("unset", str))
		return (1);
	else if (scmp("env", str))
		return (1);
	else if (scmp("exit", str))
		return (1);
	return (0);
}

int	is_controler(char *str)
{
	if (sstrcmp("\n", str))
		return (1);
	if (sstrcmp("|", str) || sstrcmp("||", str))
		return (1);
	if (sstrcmp("&", str) || sstrcmp("&&", str))
		return (1);
	if (sstrcmp(";", str) || sstrcmp(";;", str) || sstrcmp(";&", str))
		return (1);
	if (sstrcmp(";;&", str) || sstrcmp("|&", str))
		return (1);
	if (sstrcmp("(", str) || sstrcmp(")", str))
		return (1);
	return (0);
}

int	is_redirect(char *str)
{
	if (sstrcmp(">|", str))
		return (1);
	if (sstrcmp("<", str) || sstrcmp(">", str))
		return (1);
	if (sstrcmp("<<", str) || sstrcmp(">>", str))
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
		return (1);
	}
	else if (find_absolute_path(cmd, new_node, str))
		return (1);
	return (0);
}
