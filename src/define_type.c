/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:15:44 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/17 13:46:34 by mloureir         ###   ########.fr       */
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

int is_controler(char *str)
{
    if (scmp("\n", str))
        return (1);
    if (scmp("|", str) || scmp("||", str))
        return (1);
    if (scmp("&", str) || scmp("&&", str))
        return (1);
    if (scmp(";", str) || scmp(";;", str) || scmp(";&", str))
        return (1);
    if (scmp(";;&", str) || scmp("|&", str))
        return (1);
    if (scmp("(", str) || scmp(")", str))
        return (1);
    return (0);
}