/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   103_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:22:13 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 13:50:52 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*send_shell_env(void)
{
	char	*toret;
	char	buffer[PATH_MAX];
	char	*toadd;
	int		i;

	i = 0;
	toadd = "/minishell";
	toret = ft_strdup(getcwd(buffer, PATH_MAX));
	while (toadd[i])
	{
		toret = strjoinchr(toret, toadd[i]);
		i++;
	}
	return (toret);
}

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
	if (node.equal == 0)
		return (toret);
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
	while (c_envp[c.j].var_name)
		c.j++;
	toret = ft_calloc(c.j + 1, sizeof(char *));
	while (c_envp[c.i].var_name)
	{
		toret[c.i] = var_to_char(c_envp[c.i]);
		c.i++;
	}
	toret[c.i] = NULL;
	return (toret);
}

void	change_env_value(char *var_name, char *value)
{
	t_c_envp	*b_env;
	int			i;

	i = 0;
	b_env = ret_env(NULL);
	while (b_env[i].var_name)
	{
		if (sstrcmp(var_name, b_env[i].var_name))
		{
			if (b_env[i].var_value)
				free(b_env[i].var_value);
			if (value)
				b_env[i].var_value = ft_strdup(value);
			b_env[i].equal = '=';
			break ;
		}
		i++;
	}
}

void	add_env_value(char *var_name, char *var_value, int i)
{
	t_c_envp	*b_env;
	t_c_envp	*n_env;

	b_env = ret_env(NULL);
	n_env = ft_calloc(2 + size_env(b_env), sizeof(t_c_envp));
	while (b_env[i].var_name)
	{
		n_env[i].var_name = ft_strdup(b_env[i].var_name);
		free(b_env[i].var_name);
		if (b_env[i].var_value)
		{
			n_env[i].var_value = ft_strdup(b_env[i].var_value);
			free(b_env[i].var_value);
		}
		n_env[i].equal = b_env[i].equal;
		i++;
	}
	n_env[i].var_name = ft_strdup(var_name);
	n_env[i].var_value = ft_strdup(var_value);
	n_env[i].equal = '=';
	n_env[i + 1].var_name = NULL;
	n_env[i + 1].var_value = NULL;
	ret_env(n_env);
}
