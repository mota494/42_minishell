/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   103_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:22:13 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/21 14:27:26 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_to_char(t_c_envp node)
{
	char	*toret;
	t_count	c;

	start_counters(&c);
	toret = initalize_str();
	while (node.var_name[c.d])
	{
		toret = strjoinchr(toret, node.var_name[c.d]);
		c.d++;
	}
	toret = strjoinchr(toret, '=');
	while (node.var_value[c.i])
	{
		toret = strjoinchr(toret, node.var_value[c.i]);
		c.i++;
	}
	return (toret);
}

char	**send_env(void)
{
	char		**toret;
	t_c_envp	*c_envp;
	t_count		c;

	start_counters(&c);
	c_envp = ret_env(NULL);
	while (c_envp[c.d].var_name)
		c.d++;
	toret = ft_calloc(c.d + 1, sizeof(char *));
	while (c_envp[c.i].var_name)
	{
		toret[c.i] = var_to_char(c_envp[c.i]);
		c.i++;
	}
	toret[c.i] = NULL;
	return (toret);
}
