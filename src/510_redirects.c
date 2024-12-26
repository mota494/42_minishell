/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   510_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:37:54 by codespace         #+#    #+#             */
/*   Updated: 2024/12/26 17:09:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	redirect_outfile(char **args, char *red)
{
	int	fd;
	int	i;
	char *file_name;

	file_name = NULL;
	i = -1;
	while (args[++i])
		if (!is_redirect(args[i]))
	file_name = ft_strdup(args[i]);
	if (sstrcmp(">", red))
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(file_name);
}

void	redirect_infile(char **args)
{
	int	fd;
	int	i;
	char *file_name;

	i = -1;
	while (args[++i])
	{
		if (sstrcmp(args[i], "<") && args[i + 1])
		{
			file_name = ft_strdup(args[i + 1]);
			break ;
		}
	}
	fd = open(file_name, O_RDONLY);
	ft_printf(2, "the file name is: [%s]\n", file_name);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(file_name);
}

void	ft_redirect(char **args, char *red)
{
	if (sstrcmp("<", red))
		redirect_infile(args);
	else if (sstrcmp(">>", red) || sstrcmp(">", red))
		redirect_outfile(args, red);
}

void	check_red(char **args)
{
	int	i;
	char *red;

	i = -1;
	red = NULL;
	while (args[++i])
	{
		if (is_redirect(args[i]) == 1)
			red = ft_strdup(args[i]);
	}	
	if (red)
	{
		ft_redirect(args, red);
		free (red);
	}
}

char	**get_cmdline(t_token *token)
{
	int		num_token;
	char	**args;
	int		i;

	num_token = count_tokens(token);
	args = malloc(sizeof(char *) * (num_token + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (token && sstrcmp(token->cmd_line, "|") == 0)
	{
		args[i] = alocpy(token->cmd_line);
		token = token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	handle_redirect(t_token *token)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_cmdline(current_token);
	check_red(args);
	free_args(args);
}

// void	handle_redirect(t_token *token)
// {
// 	t_token	*current = token;

// 	while (current)
// 	{
// 		if (current->type == redirect)
// 		{
// 			if (sstrcmp(current->cmd_line, "<") == 1)
// 			{
// 				int fd = open(current->next->cmd_line, O_RDONLY);
// 				if (fd < 0)
// 				{
// 					perror("minishell");
// 					exit(1);
// 				}
// 				dup2(fd, STDIN_FILENO);
// 				close(fd);
// 			}
// 			else if (sstrcmp(current->cmd_line, ">") == 1 || sstrcmp(current->cmd_line, ">>") == 1)
// 			{
// 				int fd = open(current->next->cmd_line,
// 							  O_WRONLY | O_CREAT | (sstrcmp(current->cmd_line, ">>") == 1 ? O_APPEND : O_TRUNC),
// 							  0644);
// 				if (fd < 0)
// 				{
// 					perror("minishell");
// 					exit(1);
// 				}
// 				dup2(fd, STDOUT_FILENO);
// 				close(fd);
// 			}
// 			current = current->next; // Ignorar o próximo token (nome do arquivo)
// 		}
// 		current = current->next;
// 	}
// }

