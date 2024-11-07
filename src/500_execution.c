/*                                                        :::      ::::::::   */
/*   500_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@42porto.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:57:50 by mloureir          #+#    #+#             */
/*   Updated: 2024/10/18 14:37:03 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

/* aloca memória para os Process ids retornados 
pela chamada da função fork*/
int	alloc_pids(t_shell *cmd)
{
	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * cmd->n_inputs);
	if (!cmd->pids)
	{
		perror("Memory allocation issue - alloc_pids");
		return (1);
	}
	return (0);
}

/* conta quantos comandos e builtins há na pipeline */
int	count_tokens(t_token *current_token)
{
	int count;
	
	count = 0;
	while (current_token && sstrcmp(current_token->cmd_line, "|") != 1)
	{
		count++;
		current_token = current_token->next;
	}
	return (count);
}
/** Função auxiliar que identifica os comandos/builtins e seus argumentos
 * Retorna  matriz de strings comando e argumentos
 * segundo argumento da execve. */
char	**get_command_tokens(t_token *token)
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

/*libera a matriz de argumentos dos comandos e builtins*/
void	free_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/* Verifica se o comando é um built-in e o executa se for.
 * Retorna 1 se for built-in, 0 se não for. */
int	call_builtin(char **args, t_shell *cmd)
{
	if (!args || !args[0])
		return (0);
	if (sstrcmp(args[0], "cd") == 1)
	{
		cd(cmd);
		return (1);
	}
	else if (sstrcmp(args[0], "exit") == 1)
	{
		cmd->error_code = exit_main(cmd);
		return (1);
	}
	else if (sstrcmp(args[0], "echo") == 1)
	{
		echo_main(cmd);
		return (1);
	}
	else if (sstrcmp(args[0], "pwd") == 1)
		return (pwd(cmd));
	else if (sstrcmp(args[0], "env") == 1)
	{
		builtin_env();
		return (1);
	}
	return (0);
}

/** No caso da execução corresponder a apenas um builtin,
 * a funçao one_builtin executa-o no processo pai */
int	one_builtin(t_shell *cmd)
{
	t_token	*current_token;
	char	**args;

	current_token = cmd->token;
	if (current_token->type == builtin)
	{
		args = get_command_tokens(current_token);
		while (current_token)
		{
			if (current_token->type == pipes)
				return (1);
			current_token = current_token->next;
		}
		call_builtin(args, cmd);
		free_args(args);
		return (0);
	}
	return (1);
}

/*executa os builtins*/
int	execute_builtin(t_shell *cmd, t_token *token)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_command_tokens(current_token);
	call_builtin(args, cmd);
	free_args(args);
	return (0);
}

/*executa os comandos*/
int	execute_command(t_token *token, char **envp)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_command_tokens(current_token);
	if (execve(current_token->path_name, args, envp) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}

void	run_cmdx_builtx(t_shell *cmd, t_token *current, char **envp)
{
	if (current && current->type == builtin)
		execute_builtin(cmd, current);
	else if (current && current->type == command)
		execute_command(current, envp);
	exit(0);
}

t_token	*get_next(t_token *current)
{
	t_token *temp;

	temp = current->next;
	while (temp)
	{
		if (temp->type == builtin || temp->type == command)
			break ;
		temp = temp->next;
	}
	return (temp);
}

int	execute_pipeline(t_shell *cmd, char **envp)
{
	int		i;
	int	p[2];
	int	help;
	t_token *head;

	if (cmd->n_inputs == 1 && cmd->n_builtin == 1)
	{
		one_builtin(cmd);
		return (0);
	}
	if ((alloc_pids(cmd) != 0))
		return (1);
	i = 0;
	help = dup(STDIN_FILENO);
	head = cmd->token;
	while (cmd->token)
	{	
		pipe(p);
		cmd->pids[i] = fork();
		if (cmd->pids[i] == -1)
			return (1);
		if (cmd->pids[i] == 0)
		{
			if (i != 0)
				dup2(help, STDIN_FILENO);	
			if (cmd->n_inputs > 1 && i != cmd->n_inputs - 1)
				dup2(p[1], STDOUT_FILENO);
			run_cmdx_builtx(cmd, cmd->token, envp);
			close(p[0]);
			close(p[1]);
			close(help);
		}
		dup2(p[0], help);
		close(p[0]);
		close(p[1]);
		i++;
		cmd->token = get_next(cmd->token);
	}
	cmd->token = head;
	close(help);
	wait_for_child(cmd);
	return (0);
}

