/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:58:43 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/02 20:21:28 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_echo(t_token *cmd)
{
	t_token	*temp;
	int		toret;

	temp = cmd;
	toret = 0;
	while (temp)
	{
		if (temp->type != string)
			return (toret);
		temp = temp->next;
		toret++;
	}
	return (toret);
}

int	check_echo_flag(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	print_echo(t_token *cmd)
{
	int	end_flag;
	int	is_n;
	int	to_print;

	end_flag = 1;
	is_n = 0;
	to_print = count_echo(cmd);
	while (to_print > 0 && cmd)
	{
		to_print--;
		if (check_echo_flag(cmd->cmd_line) && end_flag != 0)
			is_n = 1;
		else if (to_print > 0 && ft_strlen(cmd->cmd_line) > 0)
		{
			printf("%s ", cmd->cmd_line);
			end_flag = 0;
		}
		else if (to_print == 0 && ft_strlen(cmd->cmd_line) > 0)
			printf("%s", cmd->cmd_line);
		cmd = cmd->next;
	}
	if (is_n == 0)
		printf("\n");
}

void	echo_main(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	temp = temp->next;
	print_echo(temp);
	cmd->error_code = 0;
}
