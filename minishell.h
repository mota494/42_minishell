/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:04 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/03 16:27:10 by mloureir         ###   ########.pt       */
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
	char			*eof;
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
	bool			heredoc;
	bool			doc_leave;
	bool			eof_quotes;
	pid_t			*pids;
	t_fd			*p_fds;
	t_exec			*exec;
	char			**copy_envp;
	int				line_len;
	int				pids_alloc;
	pid_t			heredoc_pid;
	char			**filename;
}					t_shell;

/* == utils == */
char			*alocpy(char *str);
t_token			*add_node(t_shell *cmd, char *content, int id);
void			print_list(t_shell *cmd);
void			init_path_dirs(t_shell *cmd, char **envp);
char			*strjoinchr(char *oldtoret, char car);
/* == utils2 == */
void			jump_spaces(char *line);
int				ft_ispace(int c);
int				scmp(char *tocomp, char *str);
int				is_there_pipe(t_token *cmd);
int				var_exist(char *str);
/* == utils3 == */
int				sstrcmp(char *tocomp, char *str);
void			del_char(char *str, int to_del);
int				fix_exit(int val);
int				count_command(t_token *cmd);
int				ft_iseparator(int c);
/* == utils4 == */
void			start_counters(t_count *counters);
char			*initalize_str(void);
int				count_builtins(t_token *cmd);
int				check_equal(char *str);
int				check_var_name(char *str);
/* == utils5 == */
int				is_quote(int c);
int				find_quote_type(char *str);
size_t			size_env(t_c_envp *b_env);
int				return_error_code(t_shell *sh);
long long int	ft_atoll(const char *nptr);
/* == utils6 == */
int				count_args(t_token *cmds);
int				is_var_char(int c);
int				is_env_char(int c);
int				count_pipes(t_token *sh);
char			*get_doc_file(char *toret);
/* == free == */
void			free_copy_envp(t_shell *cmd);
void			free_dirs(t_shell *cmd);
void			free_all(t_shell *cmd);
void			free_env(t_shell *cmd);
void			free_pids(t_shell *cmd);
/* == free2 == */
void			free_for_heredoc(t_shell *cmd);
void			unlink_files(t_shell *cmd);
/* == main == */
void			reset_fds(t_shell *cmd, int fd_in, int fd_out);
void			read_command(t_shell *cmd);
void			init_tshell(t_shell *cmd, char **envp);
void			check_input(int ac, char **av);
int				main(int ac, char **av, char **envp);
/* == main_loop == */
void			minishell_loop(t_shell *cmd, char *line);
/* == env == */
void			fix_env(void);
t_c_envp		*ret_env(t_c_envp *tosend);
char			*get_env_var(char *env);
char			*get_env(char *var);
void			copy_envs(t_shell *cmd, char **envp);
/* == env_utils == */
char			*send_shell_env(void);
char			*var_to_char(t_c_envp node);
char			**send_env(void);
void			change_env_value(char *var_name, char *value);
void			add_env_value(char *var_name, char *var_value, int i);
/* == check_syntax == */
int				check_quotes(t_shell *cmd, char *str);
void			remove_spaces(char *str);
int				check_operators(t_shell *cmd, char *str);
int				check_syntax(t_shell *cmd, char *line);
void			loop_quotes(char *str, int *double_quotes, int *single_quotes);
/* == syntax_utils == */
char			*find_quote_closure(char *str, int *i, char quote_type);
char			is_operator(char c);
/* == operators_check == */
int				check_pipe(t_shell *cmd, char *str, int op_index);
int				check_next_op(t_shell *cmd, char *str, int op_index);
int				check_append(t_shell *cmd, char *str, int i);
int				check_redout_apend(t_shell *cmd, char *str, int op_index);
int				check_redin_heredoc(t_shell *cmd, char *str, int op_index);
/* == operators_check2 == */
int				check_heredoc(t_shell *cmd, char *str, int i);
/* == syntax_error == */
void			print_error(t_shell *cmd, char *error_type,
					int error_code, char *compl);
/* == get_line == */
void			clean_line(char *cmd, char *line);
t_types			get_type(t_shell *mshell, t_token *new_node,
					char *cmd, char *orig);
char			*get_cmd(char *line);
void			tokenize(char *line, t_shell *cmd);
/* == get_line_utils == */
char			*adv_separator(char *oldtoret, char *line, int *pos);
char			*jump_quotes(char *oldtoret, char *line, int *pos, int quote);
char			*get_token(char *oldtoret, char *line, int *pos);
/* == define_type == */
int				is_builtin(char *str);
int				is_controler(char *str);
int				is_redirect(char *str);
int				is_var(char *str);
int				is_command(t_shell *cmd, t_token *new_node, char *str);
/* == define_type_utils == */
int				find_slash(char *str);
char			*concatenate(char *dir, char *str);
int				find_absolute_path(t_shell *cmd, t_token *new_node, char *str);
/* == parser == */
int				check_err(t_shell *cmd);
void			get_redirect_type(t_token *sh);
void			get_folder_type(t_token *sh);
void			parser(char *line, t_shell *cmd);
/* == parse_line == */
char			*parse_dbl_quotes(char *oldtoret, char *o_line, int *pos);
char			*parse_sgl_quotes(char *oldtoret, char *o_line, int *pos);
char			*parse_line(char *o_line);
/* == parser_get_replace_var == */
char			*return_var_value(char *oldtoret, char *var_value);
char			*get_replace_var(char *orig, int *pos, char *oldtoret);
/* == parser_vars_dollar == */
int				c_if_wrap(char *str, int *pos);
char			*rm_dollar(char *str, int *pos, char *oldtoret);
char			*not_rm_dollar(char *str, int *pos, char *oldtoret);
char			*get_error_code(int *pos, char *oldtoret);
char			*parse_dollar(char *cmd, int *pos, char *oldtoret, int i_quote);
/* == parser_special == */
void			check_specials(t_token *cmd);
void			special_case(t_shell *cmd);
/* == parser_tilde == */
char			*sub_tilde(char *old_cmd);
void			tilde(t_token *cmd);
/* == heredoc == */
void			heredoc_read(t_shell *cmd, int fd);
int				ft_read(t_shell *cmd, int fd);
int				heredoc(t_shell *cmd, int i);
int				how_many_heredoc(t_token *temp);
void			heredoc_son(t_shell *cmd, t_token *temp);
/* == heredoc_utils == */
char			*putnbr(int i);
int				is_there_quote(char *str);
char			*parser_heredoc(t_shell *cmd, char *str);
char			*get_name(char *char_nb);
void			find_heredoc(t_shell *cmd);
void			heredoc_loop(t_shell *cmd, t_token *temp, int i);
/* == heredoc_signals == */
void			heredoc_sighandle(int signo);
void			heredoc_sighandle(int signo);
void			update_leave(void);
void			heredoc_signals(void);
/* == execution == */
char			**only_cmd_arg(char **cmdline);
t_token			*get_next(t_token *current);
void			child_process(t_shell *cmd, char **envp, int help, int i);
int				execute_pipeline(t_shell *cmd, char **envp);
/* == exectuion_run == */
void			call_builtin(char **args, t_shell *cmd);
int				one_builtin(t_shell *cmd);
int				execute_builtin(t_shell *cmd, char **args);
int				execute_command(t_token *token, char **envp, char **args);
void			run_cmdx_builtx(t_shell *cmd, t_token *current, char **envp);
/* == exec_utils == */
char			**get_command_line(t_shell *cmd);
int				alloc_pids(t_shell *cmd);
int				count_tokens(t_token *current_token);
char			**get_command_tokens(t_token *token);
void			free_args(char **args);
/* == exec_utils2 == */
char			**find_command_line(t_shell *cmd);
void			free_end_exec(t_shell *cmd);
/* == redirect_and_wait == */
int				wait_for_child(t_shell *cmd);
void			handle_redirect(t_token *token);
/* == redirect_one == */
void			one_redirect_handler(char **cmdline);
/* == redirects == */
char			**get_tokens(t_token *token);
void			redirect_outfile(char **args, char *red);
void			redirect_infile(char **args);
void			ft_redirect(char **args, char *red);
void			check_red(char **args);
/* == redirects_utils == */
void			free_old_cmd(char **str);
int				size_new_line(char **cmdline);
void			infile_redirect(char *file_name, char *red_type);
void			outfile_redirect(char *file_name, int mode);
void			redirect_handler(char **cmdline);
/* == cd == */
void			cd(t_shell *cmd);
void			cd_change_dir(t_shell *cmd);
void			cd_empty_args(t_shell *cmd);
/* == echo == */
int				count_echo(t_token *cmd);
int				check_echo_flag(char *str);
void			print_echo(t_token *cmd);
void			echo_main(t_shell *cmd);
/* == env_builtin == */
int				check_env_args(t_shell *cmd);
void			builtin_env(t_shell *cmd);
/* == exit == */
int				is_strdigit(char *str);
long long int	analyze_exit_arg(t_token *arg);
int				exit_main(t_shell *cmd);
/* == pwd == */
int				pwd(t_shell *cmd);
/* == unset == */
void			old_env_free(t_c_envp *c_env);
void			copy_env_values(t_c_envp *n_env,
					t_c_envp *b_env, int pos_n, int pos_b);
t_c_envp		*unset_env_value(char *var_value);
void			unset_env(t_shell *cmd);
/* == export == */
int				count_export_args(t_token *cmd);
int				check_export_flag(t_shell *cmd);
int				check_export_args(t_shell *cmd);
void			export_main(t_shell *cmd);
/* == export_print == */
void			free_ordered(t_c_envp *o_env);
void			swap_values(t_c_envp *o_env, int i);
void			order_print(t_c_envp *o_env);
void			print_ordered(t_c_envp *ord);
void			print_export(void);
/* == export_vars == */
void			change_env_var(char *toadd);
void			var_no_equal(t_c_envp *n_env, int pos, char *toadd);
void			add_var(t_c_envp *n_env, int pos, char *toadd);
void			add_env_vars(t_c_envp *n_env, t_token *cmd, int i, t_shell *sh);
void			export_new(int num_args, t_token *cmd, t_shell *sh);
/* == signals == */
int				return_last_signal(int n_signal);
void			sig_handler(int sig);
void			sig_test(int signo);
void			setup_signals(int mode);

#endif
