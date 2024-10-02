/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:04 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/02 08:21:29 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "inc.h"

/* ============ enums ===============*/

typedef enum s_types
{
	string,
	pipes,
	command,
	builtin,
	control,
	redirect,
	var,
	error,
}					t_types;

typedef enum s_quotes
{
	dbl,
	sgl,
	no,
}					t_quotes;

/* ============ structs ============ */
/*token list*/
typedef struct s_token
{
	int				cmd_id;
	char			*cmd_line;
	char			*path_name;
	t_types			type;
	t_quotes		quote;
	struct s_token	*next;
}					t_token;

/*main structure - work in progress*/
typedef struct s_shell
{
	t_token			*token;
	int				n_inputs;
	int				error_code;
	char			**path_dirs;
	bool			leave;
	pid_t			*pids;
	t_fd			*p_fds;
	t_exec			*exec;
}					t_shell;

/* ============ functions ============ */

/* ==== main.c ==== */
void				free_all(t_shell *cmd);
/* ==== parser.c ==== */
void				parser(char *line, t_shell *cmd);
/* ==== get_line_utils.c ==== */
char				*adv_dbl_quote(char *oldtoret, char *line, int *pos);
char				*adv_spaces(char *oldtoret, char *line, int *pos);
char				*adv_sig_quote(char *oldtoret, char *line, int *pos);
char				*adv_separator(char *oldtoret, char *line, int *pos);
/* ==== get_line.c ==== */
t_types				get_type(t_shell *mshell, t_token *new_node, char *cmd);
char				*get_cmd(char *line);
t_quotes			get_quote_type(char *cmd);
void				treat_line(char *line, t_shell *cmd);
/* ==== utils.c ==== */
char				*alocpy(char *str);
t_token				*add_node(t_shell *cmd, char *content, int id);
void				print_list(t_shell *cmd);
void				init_path_dirs(t_shell *cmd, char **envp);
/* ==== utils2.c ==== */
void				jump_spaces(char *line);
int					ft_ispace(int c);
int					ft_iseparator(int c);
int					scmp(char *tocomp, char *str);
char				*strjoinchr(char *str, char c);
/* ==== define_type.c ==== */
int					is_builtin(char *str);
int					is_controler(char *str);
int					is_redirect(char *str);
int					is_var(char *str);
int					is_command(t_shell *cmd, t_token *new_node, char *str);
/* ==== define_type_utils ==== */
int					find_slash(char *str);
int					find_absolute_path(t_shell *cmd, t_token *new_node, char *str);
/* ==== utils3.c ==== */
int					sstrcmp(char *tocomp, char *str);
void				del_char(char *str, int to_del);
int					fix_exit(int val);
int					true_ninput(t_token *cmds);
int					is_there_pipe(t_token *cmd);
/* ==== syntax_error.c ==== */
void				print_error(t_shell *cmd, char *error_type,
					int error_code, char *compl);
/* ==== check_syntax ==== */
int					check_syntax(t_shell *cmd, char *line);
/* ==== syntax_utils ==== */
void				trim_spaces(char **str);
void				trim_in_between(char **str);
char				is_operator(char c);
char				*find_quote_closure(char *str, int *i, char quote_type);
/* ==== operators_check ==== */
int					check_pipe(t_shell *cmd, char *str, int op_index);
int					check_next_op(t_shell *cmd, char *str, int op_index);
int					check_redout_apend(t_shell *cmd, char *str, int op_index);
int					check_redin_heredoc(t_shell *cmd, char *str, int op_index);
/* ==== operators_check2 ==== */
int					check_heredoc(t_shell *cmd, char *str, int i);

/* ==== runtime.c ==== */
void				runtime(t_shell *cmd);

/* ==== exit.c ==== */
int					exit_main(t_shell *cmd);
/* ==== echo.c ==== */
void				echo_main(t_shell *cmd);
/* ==== redirect_and_wait ==== */
void				first_redirect(t_shell *cmd);
void				last_redirect(t_shell *cmd, int i);
void				std_redirect(t_shell *cmd, int i);
void				close_fds(t_shell *cmd);
int					wait_for_child(t_shell *cmd);
/* ==== cd.c ==== */
void				cd(t_shell *cmd);
/* ==== pwd.c ==== */
int					pwd(void);

/*sstrcmp is a normal strcmp that will return 1 if the strings are correct
scmp is a strcmp but it ignores quotes and double quotes, only used for certain
actions*/

#endif
