#include "../minishell.h"

int	count_args(t_token *cmds)
{
	int	toret;
	
	toret = 0;
	cmds = cmds->next;
	while (cmds)
	{
		if (cmds->type != string)
			break ;
		cmds = cmds->next;
		toret++;
	}
	return (toret);
}

void	cd(char *path, t_shell *cmd)
{
	t_token	*temp;
	
	temp = cmd->token;
	if (count_args(temp) > 1)
	{
		printf("minishell: cd: too many arguments\n");
		cmd->error_code = 1;
	}
	if (count_args(temp) == 0)
	{
		printf("\n");
		cmd->error_code = 0;
		return ;
	}
	if ((chdir(path) == -1))
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		cmd->error_code = 1;
	}
	else
		cmd->error_code = 0;
}
