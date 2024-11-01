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

/**printf para debug - remover
 * malloc here!
 */
int	create_pipes(t_shell *cmd)
{
	int i = 0;

	cmd->p_fds = (t_fd *)malloc(sizeof(t_fd) * (cmd->n_inputs - 1));
	if (!cmd->p_fds)
	{
		perror("Memory allocation issue - pipe fds");
		return (1);
	}
	while (i < cmd->n_inputs - 1)
	{
		if (pipe(cmd->p_fds[i].fd) == -1)
		{
			perror("Error creating pipes");
			return (2);
		}
		i++;
	}
	return (0);
}
/* aloca memória para os Process ids retornados 
pela chamada da função fork*/
int	alloc_pids(t_shell *cmd)
{

	t_token *temp;
	int i;

	i = 0;
	temp = cmd->token;
	while (temp)
	{
		if (temp->type == command || temp->type == builtin)
			i++;
		temp = temp->next;
	}
	cmd->pids = (pid_t *)malloc(sizeof(pid_t) * i);
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

/* redireciona a entrada e saída dos cmds/builtins para
 * os processos se comunicarem via pipes */
void	handle_redirection(t_shell *cmd, int i)
{
	if (i == 0)
		first_redirect(cmd);
	else if (i == cmd->n_inputs - 1)
		last_redirect(cmd, i);
	else
		std_redirect(cmd, i);
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
	close_fds(cmd);
	call_builtin(args, cmd);
	free_args(args);
	return (0);
}

/*executa os comandos*/
int	execute_command(t_shell *cmd, t_token *token, char **envp)
{
	t_token	*current_token;
	char	**args;

	current_token = token;
	args = get_command_tokens(current_token);
	close_fds(cmd);
	printf("comando será executado\n");
	if (execve(current_token->path_name, args, envp) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}

void	run_cmdx_builtx(t_shell *cmd, int i, char **envp)
{
	int	pipe_id;
	t_token *current;

	pipe_id = 0;
	current = cmd->token;
	printf("run command acessada\n");
	printf("i recebido = %d\n", i);
	while (pipe_id < i)
	{
		printf("entra no loop\n");
		if (current->type == pipes)
			pipe_id++;
		current = current->next;
	}
	if (current && current->type == builtin)
		execute_builtin(cmd, current);
	else if (current && current->type == command)
		execute_command(cmd, current, envp);
}

int	execute_pipeline(t_shell *cmd, char **envp)
{
	int		i;

	// se só houver um builtin, executa e termina.
	if (one_builtin(cmd) == 0)
		return (0);
	// caso seja um comando ou uma pipeline, a execução será fita em processos filhos
	if ((create_pipes(cmd) != 0) || (alloc_pids(cmd) != 0))
		return (1);
	i = 0;
	printf("número de comandos: %d\n", cmd->n_inputs);
	while (i < cmd->n_inputs)
	{
		cmd->pids[i] = fork();
		if (cmd->pids[i] == -1)
		{
			perror("fork issue");
			return (1);
		}
		if (cmd->pids[i] == 0)
		{
			printf("i passado: %d\n", i);
			handle_redirection(cmd, i);
			close_fds(cmd);
			run_cmdx_builtx(cmd, i, envp);
		}
		i++;
	}
	close_fds(cmd);
	wait_for_child(cmd);
	//free_mem();
	return (0);
}

