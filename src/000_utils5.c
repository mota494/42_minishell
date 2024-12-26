/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:39:22 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 15:27:14 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(int c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	find_quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			break ;
		i++;
	}
	return ((int) str[i]);
}

size_t	size_env(t_c_envp *b_env)
{
	size_t	i;

	i = 0;
	while (b_env[i].var_name)
		i++;
	return (i);
}

int	return_error_code(t_shell *sh)
{
	static t_shell	*sh_address;

	if (!sh)
		return (sh_address->error_code);
	else
	{
		sh_address = sh;
		return (0);
	}
}

long long int	ft_atoll(const char *nptr)
{
	long long int	toreturn;
	int				index;
	long long int	pos;

	toreturn = 0;
	index = 0;
	pos = 1;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || nptr[index] == 32)
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			pos = pos * -1;
		index++;
	}
	while (nptr[index] >= 48 && nptr[index] <= 57)
	{
		if (toreturn + 1 > LLONG_MAX)
			return (LLONG_MAX);
		toreturn = toreturn * 10;
		toreturn = toreturn + (nptr[index] - 48);
		index++;
	}
	return (toreturn * pos);
}
