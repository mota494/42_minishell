/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiabueno <sofiabueno@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:19:40 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/24 14:43:01 by mloureir         ###   ########.fr       */
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

	new_node = malloc(sizeof(t_token));
	new_node->cmd_line = alocpy(content);
	free(content);
	new_node->next = NULL;
	new_node->quote = get_quote_type(new_node->cmd_line);
	new_node->type = get_type(cmd, new_node, new_node->cmd_line);
	new_node->cmd_id = id;
	new_node->expanded = false;
	return (new_node);
}

void	print_list(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	while (temp)
	{
		printf("token id = %d: [%s∮%s∮%d∮%d]\n",
			temp->cmd_id, temp->orig_line, temp->cmd_line,
			temp->type, temp->quote);
		temp = temp->next;
	}
}

/** saves all the directories kept in the env PATH in an arr of strings
 ** to be used to find the absolute path of a command.*/
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

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
