/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_env_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:51 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/10 23:25:31 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_env_flags(t_token *arg)
{
	if (!arg)
		return (1);
	if (arg->cmd_line[0] == '-')
	{
		if (arg->cmd_line[1] != '\0')
		{
			ft_printf(2, "minishell: env: -%c invalid option\n",
				arg->cmd_line[1]);
			return (0);
		}
	}
	return (1);
}

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
			ft_printf(2 ,"env: ‘%s’: Permission denied\n", temp->cmd_line);
			cmd->error_code = 126;
		}
		else
		{
			ft_printf(2, "env: ‘%s’: No such file or directory\n", temp->cmd_line);
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
	if (check_for_env_flags(cmd->token->next) == 0)
	{
		cmd->error_code = 125;
		return ;
	}
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
