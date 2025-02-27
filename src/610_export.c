/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:41:02 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/10 23:26:24 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_export_args(t_token *cmd)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = cmd->next;
	while (temp && temp->type == string)
	{
		if (var_exist(temp->cmd_line))
			temp = temp->next;
		else if (!check_var_name(temp->cmd_line))
			temp = temp->next;
		else if (temp->cmd_line[0] == '=')
			temp = temp->next;
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

int	check_export_flag(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token->next;
	if (!temp)
		return (1);
	if (temp->cmd_line[0] == '-')
	{
		ft_printf(2, "minishell: export: -%c invalid option\n",
			temp->cmd_line[1]);
		return (0);
	}
	return (1);
}

int	check_export_args(t_shell *cmd)
{
	t_token	*temp;
	int		d;

	temp = cmd->token;
	if (!temp->next || temp->next->type != string)
	{
		print_export();
		cmd->error_code = 0;
		return (1);
	}
	else if (!check_export_flag(cmd))
	{
		cmd->error_code = 2;
		return (1);
	}
	else
	{
		d = count_export_args(temp);
		export_new(d, temp, cmd);
		return (1);
	}
	return (0);
}

void	export_main(t_shell *cmd)
{
	if (check_export_args(cmd))
		return ;
}
