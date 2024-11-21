/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   406_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:41:02 by mloureir          #+#    #+#             */
/*   Updated: 2024/11/21 16:12:23 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_order(t_c_envp *b_env)
{
	int	i;

	i = 0;
	while (b_env[i].var_name)
	{
		b_env[i].id = (int)b_env[i].var_name[0];
		i++;
	}
}

void	print_export(void)
{
	t_c_envp	*b_env;
	t_c_envp	*o_env;

	b_env = ret_env(NULL);
	get_order(b_env);
	/*while (b_env[i].var_name)
	{
	}*/
}

int	check_export_args(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	if (!temp->next || temp->next->type != string)
	{
		print_export();
		cmd->error_code = 0;
		return (1);
	}
	return (0);
}

void	export_main(t_shell *cmd)
{
	if (check_export_args(cmd))
		return ;
}
