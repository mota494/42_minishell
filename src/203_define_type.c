/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:15:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/19 13:20:52 by mloureir         ###   ########.fr       */
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
