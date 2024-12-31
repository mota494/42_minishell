#include "../minishell.h"

char	**find_command_line(t_shell *cmd)
{
	char	**cmdline;

	cmdline = get_command_line(cmd);
	redirect_handler(cmdline);
	cmdline = only_cmd_arg(cmdline);
	return (cmdline);
}
