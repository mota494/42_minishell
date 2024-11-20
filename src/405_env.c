/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   405_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:51 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/20 15:30:16 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_args(t_shell *cmd)
{
	t_token *temp;
	struct stat buf;

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
	char	**better_env;
	t_c_envp *b_env; 
	int	i;

	i = 0;
	if (check_env_args(cmd) == 0)
		return ;
	b_env = ret_env(NULL);
	better_env = send_env();
	while (b_env[i].id != -1)
	{
		printf("%s\n", better_env[i]);
		i++;
	}
	i = 0;
	while (b_env[i].id != - 1)
	{
		free(better_env[i]);
		i++;
	}
}
