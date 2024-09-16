/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:48:32 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/09/16 11:12:56 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*go to utils*/
int	only_spaces(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	double_redirect(t_shell *cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i + 1]))
	{
		if (ft_strchr("|<>", str[i]) && ft_isspace(str[i + 1]))
		{
			if (str[i + 2] && ft_strchr("|<>", str[i + 2]))
			{
				syntax_err_msg(cmd, str, i + 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_last_char(t_shell *cmd, char *str)
{
	if (!str || !str[0])
		return (0);
	if (ft_strchr("|<>", str[ft_strlen(str) - 1]))
	{
		syntax_err_msg(cmd, str, ft_strlen(str) - 1);
		return (1);
	}
	return (0);
}

int	check_first_char(t_shell *cmd, char *str)
{
	if (!str || !str[0])
		return (0);
	if (ft_strchr("|<>", str[0]))
	{
		syntax_err_msg(cmd, str, 0);
		return (1);
	}
	return (0);
}
/*checar os codigos de erro*/
int	check_syntax(t_shell *cmd, char *line)
{
	line = ft_strtrim(line, " \t");
	if (check_first_char(cmd, line))
		return (1);
	if (check_last_char(cmd, line))
		return (1);
	if (double_redirect(cmd, line))
		return (1);
	return (0);
}
