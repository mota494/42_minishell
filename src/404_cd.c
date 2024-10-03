#include "../minishell.h"

int	count_args(t_token *cmds)
{
	int	toret;
	
	toret = 0;
	while (cmds)
	{
		if (cmds->type != string)
			break ;
		cmds = cmds->next;
		toret++;
	}
	return (toret);
}

void	cd(t_shell *cmd)
{
	t_token	*temp;
	
	temp = cmd->token;
	temp = temp->next;
	if (count_args(temp) > 1)
	{
		printf("minishell: cd: too many arguments\n");
		cmd->error_code = 1;
	}
	if (count_args(temp) == 0)
	{
		cmd->error_code = 0;
		return ;
	}
	if ((chdir(temp->cmd_line) == -1))
	{
		printf("bash: cd: %s: No such file or directory\n", temp->cmd_line);
		cmd->error_code = 1;
	}
	else
		cmd->error_code = 0;
}
