/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   401_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:43:19 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/25 09:43:23 by mloureir         ###   ########.fr       */
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

int	analyze_exit_arg(t_token *arg)
{
	int	toret;

	if (!arg)
		return (0);
	if (is_strdigit(arg->cmd_line) == 1)
		toret = ft_atoi(arg->cmd_line);
	else
		toret = 2;
	return (toret);
}

int	exit_main(t_shell *cmd)
{
	int	exit_code;

	if (cmd->token->cmd_id != 0)
		return (0);
	else if (cmd->n_inputs > 1)
		return (0);
	exit_code = analyze_exit_arg(cmd->token->next);
	cmd->leave = true;
	write(1, "exit\n", 5);
	if (exit_code == 2)
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->token->next->cmd_line);
	return (exit_code);
}
