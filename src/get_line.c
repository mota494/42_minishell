/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:34 by mloureir          #+#    #+#             */
/*   Updated: 2024/09/17 15:25:57 by mloureir         ###   ########.fr       */
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

t_types	get_type(char *cmd)
{
	if (is_builtin(cmd) == 1)
		return (builtin);
	else if (cmd[0] == 39 || cmd[0] == 34)
        return (string);
	else if (is_controler(cmd) == 1)
		return (control);
	return (string);
}
char	*get_cmd(char *line)
{
	char	*toret;
	int		i;

	i = 0;
	toret = ft_calloc(1 ,1);
	if (ft_iseparator(line[i]) == 1)
		toret = adv_separator(toret, line, &i);
	else
		toret = adv_spaces(toret, line, &i);
	clean_line(toret, line);
	return (toret);
}

void	treat_line(char *line, t_shell *cmd)
{
	t_token *cmd_list;

	jump_spaces(line);
	cmd->token = add_node(get_cmd(line));
	cmd->n_inputs += 1;
	cmd_list = cmd->token;
	while (ft_strlen(line) > 0)
	{
		jump_spaces(line);
		if (ft_strlen(line) > 0)
		{
			while (cmd->token->next)
				cmd->token = cmd->token->next;
			cmd->token->next = add_node(get_cmd(line));
			cmd->n_inputs += 1;
		}
	}
	while (cmd_list)
	{
		printf("[Input:%s | Type:%u]\n", cmd_list->cmd_line, cmd_list->type);
		cmd_list = cmd_list->next;
	}
}
