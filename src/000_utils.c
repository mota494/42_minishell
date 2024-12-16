/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:40 by mloureir          #+#    #+#             */
/*   Updated: 2024/12/16 09:46:00 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*alocpy(char *str)
{
	char	*toret;
	int		i;

	if (!str)
		return (NULL);
	toret = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (!toret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		toret[i] = str[i];
		i++;
	}
	toret[i] = '\0';
	return (toret);
}

t_token	*add_node(t_shell *cmd, char *content, int id)
{
	t_token	*new_node;
	char	*helper;

	new_node = malloc(sizeof(t_token));
	new_node->orig_line = alocpy(content);
	free(content);
	new_node->cmd_line = parser_vars(new_node);
	helper = alocpy(new_node->cmd_line);
	free(new_node->cmd_line);
	new_node->cmd_line = parse_quotes(helper);
	free(helper);
	new_node->next = NULL;
	new_node->type = get_type(cmd, new_node, new_node->cmd_line,
			new_node->orig_line);
	new_node->cmd_id = id;
	new_node->expand = false;
	return (new_node);
}

void	print_list(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		printf("[%s] [%s]", temp->cmd_line, temp->orig_line);
		printf("[%d]\n", temp->type);
		temp = temp->next;
	}
}

void	init_path_dirs(t_shell *cmd, char **envp)
{
	int	found;
	int	i;

	found = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			found = 1;
			break ;
		}
	}
	if (found == 1)
		cmd->path_dirs = ft_split(envp[i] + 5, ':');
	else
		cmd->path_dirs = NULL;
}
