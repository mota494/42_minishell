/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   103_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:22:13 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/22 12:33:12 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_to_char(t_c_envp node)
{
	char	*toret;
	t_count	c;

	start_counters(&c);
	c.d = ft_strlen(node.var_value);
	c.i = ft_strlen(node.var_name);
	toret = malloc(c.i + c.d + 2);
	while (node.var_name[c.j])
	{
		toret[c.j] = node.var_name[c.j];
		c.j++;
	}
	c.j++;
	toret[c.j] = '=';
	while (node.var_value[c.p])
	{
		toret[c.j + c.p] = node.var_value[c.p];
		c.p++;
	}
	toret[c.j + c.p] = '\0';
	return (toret);
}

char	**send_env(void)
{
	char	**toret;
	t_c_envp *c_envp;
	t_count	c;

	start_counters(&c);
	c_envp = ret_env(NULL);
	while (c_envp[c.d].id != -1)
		c.d++;
	toret = malloc(sizeof(char *) * c.d);
	while (c_envp[c.i].id != -1)
	{
		toret[c.i] = var_to_char(c_envp[c.i]);
		c.i++;
	}
	return (toret);
}
