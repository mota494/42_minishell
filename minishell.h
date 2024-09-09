/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:04 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/09 21:50:13 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "includes/libft/libft.h"


/*structs*/

typedef enum s_types
{
	string,
	pipe,
	command,
	builtin,
}	t_types;

/*token list*/
typedef struct s_token
{
	char			*cmd_line;
	t_types			type;
	struct s_token	*next;
}			t_token;

/*main structure - work in progress*/
typedef struct s_shell
{
	t_token	*token;
}			t_shell;

#endif
