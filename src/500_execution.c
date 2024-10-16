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


/** 
 * Função auxiliar que identifica os comandos e seus argumentos
 * e ignora os pipes. Retorna  matriz de strings comando e argumentos
 * segundo argumento da execve.
 * fazer uma funcao que conta quantos tokens tem ate o final ou ate ao 
 * priximo pipe para substituir esse 10
 */
int	count_tokens(t_token *current_token)
{
	int count = 0;
	while (current_token && strcmp(current_token->cmd_line, "|") != 0)
	{
		count++;
		current_token = current_token->next;
	}
	return (count);
}
char **get_command_tokens(t_token *token)
{
	int token_count = count_tokens(token);
	char **args = malloc(sizeof(char *) * (token_count + 1));
	int i = 0;
	if (!args)
		return (NULL);
	while (token && strcmp(token->cmd_line, "|") != 0)
	{
		args[i++] = ft_strdup(token->cmd_line);
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

/**
 * Verifica se o comando é um built-in e o executa se for.
 * Retorna 1 se for built-in, 0 se não for.
 */
int	execute_builtin(char **args, t_shell *cmd)
{
	if (strcmp(args[0], "cd") == 0)
	{
		cd(cmd);
		return (1);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		exit_main(cmd);
		return (1);
	}
	else if (strcmp(args[0], "echo") == 0)
	{
		echo_main(cmd);
		return (1);
	}
	else if (strcmp(args[0], "pwd") == 0)
		return (pwd());
	return (0);
}

void handle_redirection(t_shell *cmd, int i)
{
	if (i == 0)
		first_redirect(cmd);
	else if (i == cmd->n_inputs - 1)
		last_redirect(cmd, i);
	else
		std_redirect(cmd, i);
}

int	execute_command(t_shell *cmd, char **args, t_token *current_token, char **envp, int i)
{
	cmd->pids[i] = fork();
	if (cmd->pids[i] == -1)
		return (1);
	if (cmd->pids[i] == 0)
	{
		handle_redirection(cmd, i);
		close_fds(cmd);
		//printf("%s\n", current_token->path_name);
		if (execve(current_token->path_name, args, envp) == -1)
			perror("execve");
	}
	return (0);
}

void advance_to_next_command(t_token **current_token)
{

	while (*current_token && strcmp((*current_token)->cmd_line, "|") != 0)
		*current_token = (*current_token)->next;
	if (*current_token && strcmp((*current_token)->cmd_line, "|") == 0)
		*current_token = (*current_token)->next;
	if (*current_token)
		printf("current token is %s\n", (*current_token)->cmd_line);
	else
		printf("current token is NULL\n");
}

void	free_args(char **args)
{
	int i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/*fazer uma free_args que libere uma matriz de strings*/
int execute_pipeline(t_shell *cmd, char **envp)
{
	int i = 0;
	char **args;
	t_token *current_token = cmd->token;

	if (create_pipes(cmd) != 0 || alloc_pids(cmd) != 0)
		return (1);
	while (i < cmd->n_inputs && current_token)
	{
		args = get_command_tokens(current_token);
		if (!args)
			return (1);
		if (current_token->type == builtin)
		{
			handle_redirection(cmd, i);
			close_fds(cmd);
			execute_builtin(args, cmd);
			free_args(args);
			advance_to_next_command(&current_token);
			i++;
			continue;
		}
		else
		{
			close_fds(cmd);
			if (execute_command(cmd, args, current_token, envp, i) != 0)
			{
				free_args(args);
				return (1);
			}
			free_args(args);
			advance_to_next_command(&current_token);
			i++;
		}
	}
	close_fds(cmd);
	wait_for_child(cmd);
	return (0);
}
