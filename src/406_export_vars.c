/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   406_export_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:34:21 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/26 10:06:47 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env_vars(t_c_envp *n_env, t_token *cmd)
{
	
}

void	export_new(int num_args, t_token *cmd, t_shell *sh)
{
	t_c_envp	*b_env;
	t_c_envp	*n_env;
	int		i;

	i = 0;
	b_env = ret_env(NULL);
	n_env = malloc(sizeof(t_c_envp) * (size_env(b_env) + num_args + 1));
	while (b_env[i].var_name)
	{
		n_env[i].var_name = ft_strdup(b_env[i].var_name);
		free(b_env[i].var_name);
		if (b_env[i].var_value)
		{
			n_env[i].var_value = ft_strdup(b_env[i].var_value);
			free(b_env[i].var_value);
		}
		i++;
	}
	add_env_vars(n_env, cmd);
	free(b_env);
}
