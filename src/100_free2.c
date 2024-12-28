#include "../minishell.h"

void    free_for_heredoc(t_shell *cmd)
{
    if (cmd->filename)
	{
        free_args(cmd->filename);
        cmd->filename = NULL;
	}
    if (cmd->eof)
    {
        free(cmd->eof);
        cmd->eof = NULL;        
    }
}
void    unlink_files(t_shell *cmd)
{
    int i;

    i = 0;
	while (cmd->filename[i])
    {
        unlink(cmd->filename[i]);
        i++;
    }  
}