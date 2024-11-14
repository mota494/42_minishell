/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   103_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:30:31 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/14 17:11:10 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fix_env(void)
{
	t_c_envp	*b_env;
	int			i;
	int			help;

	i = 0;
	b_env = ret_env(NULL);
	while (b_env[i].id != -1)
	{
		if (sstrcmp("SHLVL", b_env[i].var_name))
		{
			help = ft_atoi(b_env[i].var_value);
			help++;
			b_env[i].var_value = ft_itoa(help);
			break ;
		}
		i++;
	}
}

t_c_envp	*ret_env(t_c_envp *tosend)
{
	static t_c_envp	*toret;

	if (tosend)
		toret = tosend;
	return (toret);
}

char	*get_env_var(char *env)
{
	char	*var;
	int		i;

	i = 0;
	var = initalize_str();
	while (env[i] != '=' && env[i] != '\0')
	{
		var = strjoinchr(var, env[i]);
		i++;
	}
	return (var);
}

char	*get_env(char *var)
{
	int			i;
	t_c_envp	*b_env;

	i = 0;
	b_env = ret_env(NULL);
	while (b_env[i].id != -1)
	{
		if (sstrcmp(var, b_env[i].var_name) == 1)
			return (b_env[i].var_value);
		i++;
	}
	return (NULL);
}

void	copy_envs(t_shell *cmd, char **envp)
{
	t_count	c;

	start_counters(&c);
	while (envp[c.d])
		c.d++;
	c.d++;
	cmd->c_envp = malloc(sizeof(t_c_envp) * c.d);
	while (envp[c.i])
	{
		cmd->c_envp[c.i].var_name = get_env_var(envp[c.i]);
		cmd->c_envp[c.i].var_value = alocpy(getenv(cmd->c_envp[c.i].var_name));
		cmd->c_envp[c.i].id = c.i;
		c.i++;
	}
	cmd->c_envp[c.i].id = -1; 
	ret_env(cmd->c_envp);
	fix_env();
}
