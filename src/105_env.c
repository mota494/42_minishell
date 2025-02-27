/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   103_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:30:31 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/02 16:23:58 by mloureir         ###   ########.fr       */
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
	while (b_env[i].var_name)
	{
		if (sstrcmp("SHLVL", b_env[i].var_name))
		{
			help = ft_atoi(b_env[i].var_value);
			help++;
			free(b_env[i].var_value);
			b_env[i].var_value = ft_itoa(help);
		}
		if (sstrcmp("SHELL", b_env[i].var_name))
		{
			free(b_env[i].var_value);
			b_env[i].var_value = send_shell_env();
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
	while (b_env[i].var_name)
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
		if (check_equal(envp[c.i]))
			cmd->c_envp[c.i].equal = '=';
		else
			cmd->c_envp[c.i].equal = 0;
		c.i++;
	}
	cmd->c_envp[c.i].var_value = NULL;
	cmd->c_envp[c.i].var_name = NULL;
	ret_env(cmd->c_envp);
	fix_env();
}
