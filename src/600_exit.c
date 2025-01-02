/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:43:19 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/02 17:49:03 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_strdigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long int	analyze_exit_arg(t_token *arg, int old_error)
{
	long long int	toret;

	if (!arg)
		return (old_error);
	if (sstrcmp(arg->cmd_line, "|"))
		return (old_error);
	if (is_strdigit(arg->cmd_line) == 1)
	{
		toret = ft_atoll(arg->cmd_line);
		if (toret >= LLONG_MAX || toret <= LLONG_MIN)
			toret = -1;
	}
	else
		toret = -1;
	return (toret);
}

int	exit_main(t_shell *cmd)
{
	if (count_args(cmd->token->next) > 1)
	{
		ft_printf(2, "minishell: exit: too many arguments\n");
		cmd->error_code = 1;
		return (0);
	}
	cmd->error_code = analyze_exit_arg(cmd->token->next, cmd->error_code);
	if (cmd->error_code == -1)
	{
		ft_printf(2, "minishell: exit: %s: numeric argument required\n",
			cmd->token->next->cmd_line);
		cmd->error_code = 2;
	}
	if (cmd->token->cmd_id == 0)
	{
		cmd->leave = true;
		write(1, "exit\n", 5);
	}
	return (cmd->error_code);
}
