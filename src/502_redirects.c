/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   502_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:37:54 by codespace         #+#    #+#             */
/*   Updated: 2024/11/25 17:55:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_infile(char **args/*, int p[2]*/)
{
	int	fd;
	int	i;
	char *file_name;

	i = -1;
	while (args[++i])
		if (!is_redirect(args[i]))
	file_name = ft_strdup(args[i]);
	fd = open(file_name, O_RDONLY);
	// if fd == -1 -> erro ao abrir o ficheiro
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(file_name);
}

void	ft_redirect(char **args, char *red/*, int p[2]*/)
{
	if (sstrcmp("<", red))
		redirect_infile(args);
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

void	handle_redirect(t_token *token /*, int p[2]*/)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_command_tokens(current_token);
	check_red(args/*, p*/);
	free_args(args);
}