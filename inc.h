#ifndef INC_H
# define INC_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "includes/libft/libft.h"

typedef struct s_index_counter
{
	size_t	i;
	size_t	count;
}		t_ic;

#endif
