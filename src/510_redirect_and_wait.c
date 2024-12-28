/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_redirect_and_wait.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:11:19 by sofiabueno        #+#    #+#             */
/*   Updated: 2024/12/27 09:26:42 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirect(t_token *token/*, int p[2]*/)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_tokens(current_token);
	check_red(args/*, p*/);
	free_args(args);
}

int	wait_for_child(t_shell *cmd)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < cmd->n_inputs)
	{
		waitpid(cmd->pids[i], &wstatus, 0);
		if (wstatus > 255)
			cmd->error_code = WEXITSTATUS(wstatus);
		else
			cmd->error_code = wstatus;
		if (wstatus == 131)
			return_last_signal(SIGQUIT);
		if (wstatus == 2)
			cmd->error_code = 2 + 128;
	}
	return (0);
}
