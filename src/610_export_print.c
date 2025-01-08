/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_export_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:35:48 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 10:19:34 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_ordered(t_c_envp *o_env)
{
	int	i;

	i = 0;
	while (o_env[i].var_name)
	{
		free(o_env[i].var_name);
		free(o_env[i].var_value);
		i++;
	}
	free(o_env);
}

void	swap_values(t_c_envp *o_env, int i)
{
	char	*temp_name;
	char	*temp_value;
	int		temp_equal;

	temp_name = ft_strdup(o_env[i].var_name);
	free(o_env[i].var_name);
	o_env[i].var_name = ft_strdup(o_env[i + 1].var_name);
	free(o_env[i + 1].var_name);
	o_env[i + 1].var_name = ft_strdup(temp_name);
	free(temp_name);
	temp_value = ft_strdup(o_env[i].var_value);
	free(o_env[i].var_value);
	o_env[i].var_value = ft_strdup(o_env[i + 1].var_value);
	free(o_env[i + 1].var_value);
	o_env[i + 1].var_value = ft_strdup(temp_value);
	free(temp_value);
	temp_equal = o_env[i].equal;
	o_env[i].equal = o_env[i + 1].equal;
	o_env[i + 1].equal = temp_equal;
}

void	order_print(t_c_envp *o_env)
{
	int		i;

	i = 0;
	while (o_env[i].var_name)
	{
		if (o_env[i + 1].var_name)
		{
			if (ft_strncmp(o_env[i].var_name, o_env[i + 1].var_name, 1024) > 0)
			{
				swap_values(o_env, i);
				i = -1;
			}
		}
		i++;
	}
}

void	print_ordered(t_c_envp *ord)
{
	t_count	c;

	start_counters(&c);
	while (ord[c.d_i].var_name)
	{
		if (ft_strlen(ord[c.d_i].var_name) == 1
			&& ord[c.d_i].var_name[0] == '_')
			c.d_i++;
		else
		{
			if (ord[c.d_i].equal == '=')
				printf("declare -x %s=\"%s\"\n", ord[c.d_i].var_name,
					ord[c.d_i].var_value);
			else
				printf("declare -x %s\n", ord[c.d_i].var_name);
			c.d_i++;
		}
	}
}

void	print_export(void)
{
	t_c_envp	*b_env;
	t_c_envp	*o_env;
	t_count		c;

	start_counters(&c);
	b_env = ret_env(NULL);
	o_env = malloc(sizeof(t_c_envp) * (size_env(b_env) + 1));
	while (b_env[c.i_i].var_name)
	{
		o_env[c.i_i].var_name = ft_strdup(b_env[c.i_i].var_name);
		o_env[c.i_i].var_value = ft_strdup(b_env[c.i_i].var_value);
		o_env[c.i_i].equal = b_env[c.i_i].equal;
		c.i_i++;
	}
	o_env[c.i_i].var_name = NULL;
	order_print(o_env);
	print_ordered(o_env);
	free_ordered(o_env);
}
