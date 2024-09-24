#include "../minishell.h"

void	check_command(t_shell *cmd)
{
	if (sstrcmp(cmd->token->cmd_line, "exit"))
		exit_main(cmd);
}

void	runtime(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (cmd->token)
	{
		check_command(cmd);
		cmd->token = cmd->token->next;
	}
	cmd->token = temp;
}
