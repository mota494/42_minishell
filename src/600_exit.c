/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:43:19 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/11 16:48:46 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_strdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long int	analyze_exit_arg(t_token *arg)
{
	long long int	nbr;

	if (!arg)
		return (1);
	if (!is_strdigit(arg->cmd_line))
		return (0);
	nbr = ft_atoll(arg->cmd_line);
	if (nbr >= LLONG_MAX || nbr <= LLONG_MIN)
		return (0);
	return (1);
}

void	actual_exit(t_shell *cmd)
{
	cmd->leave = true;
	if (cmd->token->next)
		cmd->error_code = ft_atoll(cmd->token->next->cmd_line);
	write(1, "exit\n", 5);
}

void	exit_main(t_shell *cmd)
{
	if (analyze_exit_arg(cmd->token->next) == 0)
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n",
			cmd->token->next->cmd_line);
		cmd->error_code = 2;
		cmd->leave = true;
	}
	else if (count_args(cmd->token->next) > 1)
	{
		printf("exit\n");
		ft_printf(2, "minishell: exit: too many arguments\n");
		cmd->error_code = 1;
		return ;
	}
	else if (cmd->token->cmd_id == 0)
	{
		actual_exit(cmd);
	}
	else
	{
		if (cmd->token->next)
			cmd->error_code = ft_atoll(cmd->token->next->cmd_line);
	}
}
