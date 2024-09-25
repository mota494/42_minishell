/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:59:28 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/18 10:59:29 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include "includes/libft/libft.h"
# include <stdbool.h>
# define OPERATORS "|<>"
# define ERROR_QUOTE "quotation has not been closed"
# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_DOUBLE_PIPE "syntax error near unexpected token `||'"
# define ERROR_PIPE_END "minishell does not support this type of pipe"
# define ERROR_REDIRECT "syntax error near unexpected token `newline'"
# define ERR_GENERAL "syntax error near unexpected token"

typedef struct s_index_counter
{
	size_t	i;
	size_t	count;
}		t_ic;

#endif
