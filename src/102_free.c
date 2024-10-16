#include "../minishell.h"

void	free_env(t_shell *cmd)
{
	t_count	c;

	start_counters(&c);
	while (cmd->c_envp[c.i].id != -1)
	{
		free(cmd->c_envp[c.i].var_name);
		c.i++;
	}
	free(cmd->c_envp);
}
