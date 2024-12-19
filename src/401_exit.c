/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   401_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:43:19 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/19 15:59:48 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	analyze_exit_arg(t_token *arg, int old_error)
{
	int	toret;

	if (!arg)
		return (old_error);
	if (is_strdigit(arg->cmd_line) == 1)
		toret = ft_atoi(arg->cmd_line);
	else
		toret = 2;
	return (toret);
}

int	exit_main(t_shell *cmd)
{
	cmd->error_code = analyze_exit_arg(cmd->token->next, cmd->error_code);
	if (cmd->error_code == 2)
		ft_printf(2, "minishell: exit: %s: numeric argument required\n",
			cmd->token->next->cmd_line);
	if (cmd->token->cmd_id == 0)
	{
		cmd->leave = true;
		write(1, "exit\n", 5);
	}
	return (cmd->error_code);
}
