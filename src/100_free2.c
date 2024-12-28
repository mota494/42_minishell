#include "../minishell.h"

void    free_for_heredoc(t_shell *cmd)
{
    if (cmd->filename)
	{
		free(cmd->filename);
		cmd->filename = NULL;
	}
    if (cmd->eof)
    {
        free(cmd->eof);
        cmd->eof = NULL;        
    }
}