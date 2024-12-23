/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   502_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:37:54 by codespace         #+#    #+#             */
/*   Updated: 2024/12/23 15:34:51 by mloureir         ###   ########.pt       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_tokens(t_token *token)
{
	int		num_token;
	char	**args;
	t_token	*current;
	int		i;

	current = token;
	num_token = count_tokens(current);
	args = malloc(sizeof(char *) * (num_token + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (current && strcmp(current->cmd_line, "|") != 0)
	{
		args[i] = alocpy(current->cmd_line);
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

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

void	redirect_infile(char **args/*, int p[2]*/)
{
	int	fd;
	int	i;
	char *file_name;

	i = -1;
	while (args[++i])
	{
		if (is_redirect(args[i]))
			break ;
	}
	i++;
	file_name = ft_strdup(args[i]);
	fd = open(file_name, O_RDONLY);
	ft_printf(2, "[[%s]]", file_name);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(file_name);
}

void	ft_redirect(char **args, char *red/*, int p[2]*/)
{
	if (sstrcmp("<", red))
		redirect_infile(args);
	else if (sstrcmp(">>", red) || sstrcmp(">", red))
		redirect_outfile(args, red);
}

void	check_red(char **args/*, int p[2]*/)
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
	if (red == NULL)
		return ;
	else
	{
		ft_redirect(args, red/*, p*/);
		free (red);
	}
}

void	handle_redirect(t_token *token/*, int p[2]*/)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_tokens(current_token);
	check_red(args/*, p*/);
	free_args(args);
}
