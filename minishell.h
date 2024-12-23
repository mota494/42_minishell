/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:04 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/23 10:57:59 by mloureir         ###   ########.pt       */
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
	file,
	folder,
	error,
}					t_types;

/* ============ structs ============ */
/*counts*/
typedef struct s_count
{
	size_t	i;
	size_t	j;
	size_t	d;
	size_t	p;
	int		i_i;
	int		j_i;
	int		d_i;
}					t_count;
/*token list*/
typedef struct s_token
{
	int				cmd_id;
	char			*cmd_line;
	char			*orig_line;
	char			*eof;
	char			*path_name;
	bool			expand;
	t_types			type;
	struct s_token	*next;
}					t_token;
/*copy envp*/
typedef struct s_cenvp
{
	char	*var_name;
	char	*var_value;
	char	equal;
	int		id;
}					t_c_envp;
/*main structure - work in progress*/
typedef struct s_shell
{
	t_token			*token;
	t_token			*head;
	int				n_inputs;
	int				n_builtin;
	int				n_command;
	int				error_code;
	int				fds[2];
	char			**path_dirs;
	char			**fork_cmds;
	t_c_envp		*c_envp;
	int				env_cnt;
	char			*curdir;
	bool			leave;
	pid_t			*pids;
	t_fd			*p_fds;
	t_exec			*exec;
	char			**copy_envp;
	int				line_len;
}					t_shell;

/* == sig_handler == */
int					return_last_signal(int n_signal);
void				setup_signals(int mode);	
/* == unset == */
void				unset_env(t_shell *cmd);
/* == parser == */
char				*parse_line(char *o_line);
/* ============ functions ============ */
char				*get_token(char *oldtoret, char *line, int *pos);
/* redirect */
void				handle_redirect(t_token *token /*, int p[2]*/);
/* export */
int					var_exist(char *str);
void				print_export(void);
size_t				size_env(t_c_envp *b_env);
void				export_new(int num_args, t_token *cmd, t_shell *sh);
int					check_equal(char *str);
int					is_env_char(int c);
int					check_var_name(char *str);
/* free */
void				free_pids(t_shell *cmd);
/* parser_vars */
int					already_analyzed(char *str);
int					is_quote(int c);
int					is_var_char(int c);
char				*get_replace_var(char *orig_line, int *pos, char *newtoret);
int					check_wrap(char *str, int *pos);
char				*parser_vars(t_token *cmd);
char				*addsufix(char *cmd, int *pos);
char				*addprefix(char *cmd, int *pos, char *oldtoret);
char				*parse_dollar(char *cmd, int *pos, char *oldtoret, int i_quote);
/* ==== main.c ==== */
void				free_all(t_shell *cmd);
/* ==== parser.c ==== */
int					check_err(t_shell *cmd);
void				parser(char *line, t_shell *cmd);
/* ==== get_line_utils.c ==== */
char				*adv_dbl_quote(char *oldtoret, char *line, int *pos);
char				*adv_spaces(char *oldtoret, char *line, int *pos);
char				*adv_sig_quote(char *oldtoret, char *line, int *pos);
char				*adv_separator(char *oldtoret, char *line, int *pos);
/* ==== get_line.c ==== */
t_types				get_type(t_shell *mshell, t_token *new_node, char *cmd,
						char *orig);
char				*get_cmd(char *line);
void				tokenize(char *line, t_shell *cmd);
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
char				*strjoinchr(char *oldtoret, char car);
/* ==== utils4.c ==== */
void				start_counters(t_count *counters);
char				*initalize_str(void);
int					return_error_code(t_shell *sh);
int					count_args(t_token *cmds);
long long int		ft_atoll(const char *nptr);
/* ==== define_type.c ==== */
int					is_builtin(char *str);
int					is_controler(char *str);
int					is_redirect(char *str);
int					is_var(char *str);
int					is_command(t_shell *cmd, t_token *new_node, char *str);
/* ==== define_type_utils ==== */
int					find_slash(char *str);
int					find_absolute_path(t_shell *cmd, t_token *new_node,
						char *str);
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
char				is_operator(char c);
char				*find_quote_closure(char *str, int *i, char quote_type);
/* ==== operators_check ==== */
int					check_pipe(t_shell *cmd, char *str, int op_index);
int					check_next_op(t_shell *cmd, char *str, int op_index);
int					check_redout_apend(t_shell *cmd, char *str, int op_index);
int					check_redin_heredoc(t_shell *cmd, char *str, int op_index);
/* ==== operators_check2 ==== */
int					check_heredoc(t_shell *cmd, char *str, int i);
/* ==== exit.c ==== */
int					exit_main(t_shell *cmd);
/* ==== echo.c ==== */
void				echo_main(t_shell *cmd);
/* ==== redirect_and_wait ==== */
int					wait_for_child(t_shell *cmd);
/* ==== cd.c ==== */
void				cd(t_shell *cmd);
/* ==== pwd.c ==== */
int					pwd(t_shell *cmd);
/* ==== special_case.c ==== */
void				special_case(t_shell *cmd);
void				tilde(t_token *cmd);
int					execute_pipeline(t_shell *cmd, char **envp);
/* ==== copy_evn ==== */
void				copy_envs(t_shell *cmd, char **envp);
t_c_envp			*ret_env(t_c_envp *tosend);
char				*get_env(char *var);
int					check_equal(char *str);
/* ==== free ==== */
void				free_env(t_shell *cmd);
/* === env_utils ==== */
void				add_env_value(char *var_name, char *var_value, int i);
char				**send_env(void);
void				builtin_env(t_shell *cmd);
void				change_env_value(char *var_name, char *value);
char				*send_shell_env(void);
/* ==== redifine_type ==== */
void				red_type(t_shell *cmd);
/* ==== counte ==== */
int					count_command(t_token *cmd);
int					count_builtins(t_token *cmd);
/* parse_quotes */
char				*parse_quotes(char *str);
/* exec_utils */
void				free_args(char **args);
char				**get_command_tokens(t_token *token);
int					count_tokens(t_token *current_token);
int					alloc_pids(t_shell *cmd);
void				call_builtin(char **args, t_shell *cmd);
int					one_builtin(t_shell *cmd);
int					execute_builtin(t_shell *cmd, t_token *token);
int					execute_command(t_token *token, char **envp);
void				run_cmdx_builtx(t_shell *cmd, t_token *current, char **envp);
/* export_builtin */
void				export_main(t_shell *cmd);
/* redirects */
void				handle_redirect(t_token *token /*, int p[2]*/);
char				**get_tokens(t_token *token);
/* heredoc */
void				find_heredoc(t_shell *cmd);

/*
sstrcmp is a normal strcmp that will return 1 if the strings are correct
scmp is a strcmp but it ignores quotes and double quotes, only used for certain
actions

ret_env is used to store and return a static variable, that way the copy of
evnp is available at all times without having to use a global variable

send_env returns the current envp in a matrix
*/

#endif
