/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   405_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/02 09:22:22 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_args(t_shell *cmd)
{
	t_token		*temp;
	struct stat	buf;

	temp = cmd->token;
	if (temp->next)
		temp = temp->next;
	else
		return (1);
	if (temp->type == string)
	{
		if (stat(temp->cmd_line, &buf))
		{
			printf("env: ‘%s’: Permission denied\n", temp->cmd_line);
			cmd->error_code = 126;
		}
		else
		{
			printf("env: ‘%s’: No such file or directory\n", temp->cmd_line);
			cmd->error_code = 127;
		}
		return (0);
	}
	return (1);
}

void	builtin_env(t_shell *cmd)
{
	t_c_envp	*b_env;
	int			i;

	i = 0;
	if (check_env_args(cmd) == 0)
		return ;
	b_env = ret_env(NULL);
	while (b_env[i].var_name)
	{
		if (b_env[i].equal == '=')
		{
			printf("%s", b_env[i].var_name);
			printf("=%s", b_env[i].var_value);
			printf("\n");
		}
		i++;
	}
	cmd->error_code = 0;
}
