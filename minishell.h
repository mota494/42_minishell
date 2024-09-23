/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:04 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/23 14:40:23 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "inc.h"

/* ========== define error ========== */

# define OPERATORS "|<>"
# define ERROR_QUOTE "quotation has not been closed"
# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_DOUBLE_PIPE "syntax error near unexpected token `||'"
# define ERROR_PIPE_END "minishell does not support this type of pipe"
# define ERROR_REDIRECT "syntax error near unexpected token `newline'"
# define ERR_GENERAL "syntax error near unexpected token"

/* ============ structs ============ */
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
	int		n_inputs;
	int		error_code;
}			t_shell;

/* ============ functions ============ */

/*utils.c*/
char	*alocpy(char *str);
int		ft_strcmp(char *tocomp, char *str);
t_token	*add_node(char	*content);
int		ft_isspace(int c);
/*get_line.c*/
t_types	get_type(char *cmd);
char	*strjoinchr(char *str, char c);
void	treat_line(char *line, t_shell *cmd);
/*syntax_error*/
void	print_error(t_shell *cmd, char *error_type, int error_code,
			char *compl);
/*check_syntax*/
int		check_syntax(t_shell *cmd, char *line);
/*syntax_utils*/
void	trim_spaces(char **str);
void	trim_in_between(char **str);
char	is_operator(char c);
char	*find_quote_closure(char *str, int *i, char quote_type);
/*operators_check*/
int		check_pipe(t_shell *cmd, char *str, int op_index);
int		check_redout_apend(t_shell *cmd, char *str, int op_index);
#endif
