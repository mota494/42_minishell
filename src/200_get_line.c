/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/02 08:54:31 by sofiabueno       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_line(char *cmd, char *line)
{
	int	i;

	i = 0;
	while (line[i + ft_strlen(cmd)])
	{
		line[i] = line[i + ft_strlen(cmd)];
		i++;
	}
	line[i] = '\0';
}

t_quotes	get_quote_type(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34)
			return (dbl);
		else if (cmd[i] == 39)
			return (sgl);
		i++;
	}
	return (no);
}

t_types	get_type(t_shell *mshell, t_token *new_node, char *cmd)
{
	static int	is_arg;

	if (is_controler(cmd) == 1)
	{
		is_arg = 0;
		return (control);
	}
	if (is_redirect(cmd) == 1)
	{
		is_arg = 0;
		return (redirect);
	}
	else if (is_arg == 1)
		return (string);
	else if (is_builtin(cmd) == 1)
	{
		is_arg = 1;
		return (builtin);
	}
	else if (is_command(mshell, new_node, cmd) == 1)
	{
		is_arg = 1;
		return (command);
	}
	return (error);
}

char	*get_cmd(char *line)
{
	char	*toret;
	int		i;

	i = 0;
	toret = ft_calloc(1, 1);
	if (line[i] == 39)
		toret = adv_sig_quote(toret, line, &i);
	else if (line[i] == 34)
		toret = adv_dbl_quote(toret, line, &i);
	else if (ft_iseparator(line[i]) == 1)
		toret = adv_separator(toret, line, &i);
	else
		toret = adv_spaces(toret, line, &i);
	if (toret)
		clean_line(toret, line);
	return (toret);
}

void	tokenize(char *line, t_shell *cmd)
{
	t_token	*cmd_list;
	int		i;

	i = 0;
	//jump_spaces(line);
	cmd->token = add_node(cmd, get_cmd(line), i);
	cmd->n_inputs += 1;
	cmd_list = cmd->token;
	i++;
	while (ft_strlen(line) > 0)
	{
		jump_spaces(line);
		if (ft_strlen(line) > 0)
		{
			while (cmd->token->next)
				cmd->token = cmd->token->next;
			cmd->token->next = add_node(cmd, get_cmd(line), i);
			i++;
			cmd->n_inputs += 1;
		}
	}
	cmd->token = cmd_list;
}
