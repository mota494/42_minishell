/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:04 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/13 16:36:07 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "inc.h"

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
}			t_shell;

/* ============ functions ============ */

/*get_line_utils.c*/
char	*adv_dbl_quote(char *oldtoret, char *line, int *pos);
char	*adv_spaces(char *oldtoret, char *line, int *pos);
char	*adv_sig_quote(char *oldtoret, char *line, int *pos);
/*get_line.c*/
t_types	get_type(char *cmd);
char	*get_cmd(char *line);
void	treat_line(char *line, t_shell *cmd);
/*utils.c*/
char	*alocpy(char *str); //allocs a new string and coppies the string sent to the new string
t_token	*add_node(char	*content);
int		is_builtin(char *str);
/*utils2.c*/
void	jump_spaces(char *line);
int		ft_ispace(int c);
int		ft_strcmp(char *tocomp, char *str);
char	*strjoinchr(char *str, char c); //adds the char received to the string sent
#endif
