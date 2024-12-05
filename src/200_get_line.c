/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/05 09:59:53 by mloureir         ###   ########.fr       */
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

t_types	get_type(t_shell *mshell, t_token *new_node, char *cmd, char *orig)
{
	static int	is_arg;

	if (is_controler(orig) == 1)
	{
		is_arg = 0;
		return (control);
	}
	if (is_redirect(orig) == 1)
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

char	*fix_quotest_count(char *oldtoret, char *line, int *pos)
{
	char	*newtoret;

	newtoret = alocpy(oldtoret);
	free(oldtoret);
	while (!even_quote(newtoret, 34) && line[*pos])
	{
		newtoret = strjoinchr(newtoret, line[*pos]);
		*pos += 1;
	}
	while (!even_quote(newtoret, 39) && line[*pos])
	{
		newtoret = strjoinchr(newtoret, line[*pos]);
		*pos += 1;
	}
	return (newtoret);
}

char	*get_cmd(char *line)
{
	char	*toret;
	int		i;

	i = 0;
	toret = ft_calloc(1, 1);
	if (line[i] == 39)
		toret = get_token(toret, line, &i);
	else if (line[i] == 34)
		toret = get_token(toret, line, &i);
	else if (ft_iseparator(line[i]) == 1)
		toret = adv_separator(toret, line, &i);
	else
		toret = get_token(toret, line, &i);
	if (toret)
	{
		//toret = fix_quotest_count(toret, line, &i);
		clean_line(toret, line);
	}
	return (toret);
}

void	tokenize(char *line, t_shell *cmd)
{
	t_token	*cmd_list;
	int		i;

	i = 0;
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
