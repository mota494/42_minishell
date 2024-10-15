/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   405_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:30:31 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/15 11:30:35 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *env)
{
	char	*var;
	int		i;

	i = 0;
	var = initalize_str();
	while (env[i] != '=')
	{
		var = strjoinchr(var, env[i]);
		i++;
	}
	return (var);
}

void	copy_envs(t_shell *cmd, char **envp)
{
	t_count	c;

	start_counters(&c);
	while (envp[c.d])
		c.d++;
	cmd->c_envp = malloc(sizeof(t_c_envp) * c.d);
	while (envp[c.i])
	{
		cmd->c_envp[c.i].var_name = get_env_var(envp[c.i]);
		cmd->c_envp[c.i].var_value = getenv(cmd->c_envp[c.i].var_name);
		c.i++;
	}
	cmd->c_envp[c.i].var_name = "\0";
	cmd->c_envp[c.i].var_value = "\0";
}
