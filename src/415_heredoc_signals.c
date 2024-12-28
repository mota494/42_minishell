#include "../minishell.h"

void	heredoc_sighandle(int signo)
{
	if (signo == SIGQUIT)
	{
		return_last_signal(signo);
	}
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, heredoc_sighandle);	
}
