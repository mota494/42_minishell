/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:59:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/30 16:14:51 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC_H
# define INC_H

# include <stdio.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include "includes/libft/libft.h"
# include <stdbool.h>

/********* syntax errors ********/
# define OPERATORS "|<>"
# define ERROR_QUOTE "quotation has not been closed"
# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_DOUBLE_PIPE "syntax error near unexpected token `||'"
# define ERROR_PIPE_END "minishell does not support this type of pipe"
# define ERROR_REDIRECT "syntax error near unexpected token `newline'"
# define ERR_GENERAL "syntax error near unexpected token"

/********* syntax structs ********/
typedef struct s_index_counter
{
	size_t	i;
	size_t	count;
}		t_ic;

/*Structure which contains an array of integers - a pipe's couple of fds*/
typedef struct s_fd
{
	int	fd[2];
}		t_fd;

/*Structure which keeps execve's arguments*/
typedef struct s_exec
{
	char	*pathname;
	char	**args;
	char	**dirs;
}			t_exec;

#endif
