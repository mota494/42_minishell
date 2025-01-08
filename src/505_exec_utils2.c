/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_exec_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:01:57 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/08 10:06:11 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_files(char **cmdline)
{
	int	i;
	int	temp;

	i = 0;
	while (cmdline[i])
	{
		if (sstrcmp(cmdline[i], "<"))
		{
			i++;
			temp = open(cmdline[i], O_RDONLY);
			if (temp == -1)
			{
				close(temp);
				ft_printf(2, "minishell: %s: no such file\n", cmdline[i]);
				return (0);
			}
			close(temp);
		}
		else
			i++;
	}
	return (1);
}

char	**find_command_line(t_shell *cmd)
{
	char	**cmdline;

	cmdline = get_command_line(cmd);
	if (verify_files(cmdline) == 0)
	{
		free_args(cmdline);
		return (NULL);
	}
	redirect_handler(cmdline);
	free_args(cmdline);
	cmdline = only_cmd_arg(cmd);
	return (cmdline);
}

void	free_end_exec(t_shell *cmd)
{
	free_all(cmd);
	free_env(cmd);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
