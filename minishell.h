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
#include "inc.h"

/*structs*/
typedef enum s_types
{
	string,
	pipes,
	command,
	builtin,
	error,
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
	int	n_inputs;
}			t_shell;

/* ============ functions ============ */

/*utils.c*/
char	*alocpy(char *str);
int		ft_strcmp(char *tocomp, char *str);
t_token	*add_node(char	*content);
int	ft_ispace(int c);
/*get_line.c*/
t_types	get_type(char *cmd);
void	treat_line(char *line, t_shell *cmd);
#endif
