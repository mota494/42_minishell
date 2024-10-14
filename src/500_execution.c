#include "../minishell.h"

/**printf para debug - remover
 * malloc here!
 */
int	create_pipes(t_shell *cmd)
{
	int	i;

	cmd->p_fds = (t_fd *)malloc(sizeof(t_fd) * (cmd->n_inputs - 1));
	if (!cmd->p_fds)
	{
		perror("Memory allocation issue - pipe fds");
		return (1);
	}
	i = -1;
	while (++i < cmd->n_inputs - 1)
	{
		if (pipe(cmd->p_fds[i].fd) == -1)
		{
			perror("Error creating pipes");
			return (2);
		}
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
 * e ignora os pipes. Retorna um array de strings (comando e argumentos).
 */
char **get_command_tokens(t_shell *cmd, int *index, t_token **current_token)
{
	t_token	*token;
	char	**args;
	int		i = 0;

	token = *current_token;
	args = malloc(sizeof(char *) * (cmd->n_inputs + 1));
	if (!args)
	{
		perror("Memory allocation issue - args");
		return (NULL);
	}
	while (token && token->cmd_id == *index)
	{
		if (strcmp(token->cmd_line, "|") == 0)
		{
			token = token->next;
			break;
		}
		args[i++] = alocpy(token->cmd_line);
		token = token->next;
	}
	args[i] = NULL;
	*index += 1;
	*current_token = token;
	return (args);
}

/**
 * Verifica se o comando é um built-in e o executa se for.
 * Retorna 1 se for built-in, 0 se não for.
 */
int execute_builtin(char **args, t_shell *cmd)
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
	// Adicionar outros built-ins
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

int execute_command(t_shell *cmd, char **args, t_token *current_token, char **envp, int i)
{
    printf("Forking process...\n");  // Depuração antes de chamar o fork
    
    // Iniciar o fork para criar um processo filho
    cmd->pids[i] = fork();
    if (cmd->pids[i] == -1)  // Verificação de erro no fork
    {
        perror("fork issue");
        return (1);
    }
    if (cmd->pids[i] == 0)  // Código do processo filho
    {
        printf("In child process (fork successful)...\n");  // Depuração do processo filho
        
        // Gerenciamento de redirecionamento (entrada/saída)
        handle_redirection(cmd, i);
        close_fds(cmd);  // Fechar descritores de arquivo
        
        // Verificar se o comando e o caminho estão corretos
        if (current_token && current_token->path_name)
        {
            printf("Executing command: %s with path: %s\n", args[0], current_token->path_name);
            
            // Depuração dos argumentos do comando
            int j = 0;
            while (args[j] != NULL)
            {
                printf("args[%d]: %s\n", j, args[j]);
                j++;
            }

            // Depuração para o array de ambiente
            if (envp == NULL)
            {
                printf("Environment is NULL\n");
            }
            else
            {
                int k = 0;
                while (envp[k] != NULL)
                {
                    printf("envp[%d]: %s\n", k, envp[k]);
                    k++;
                }
            }

            // Execução do comando com execve
            if (execve(current_token->path_name, args, envp) == -1)
            {
                perror("execve");  // Depuração em caso de falha do execve
            }
        }
        else
        {
            // Caso o caminho do comando não seja encontrado
            fprintf(stderr, "Command not found: %s\n", args[0]);
        }

        free(args);  // Liberar os argumentos no processo filho
        exit(EXIT_FAILURE);  // Se algo falhar, o processo filho deve sair com erro
    }
    else  // Código do processo pai
    {
        printf("In parent process (waiting for child)...\n");  // Depuração do processo pai
    }

    return (0);  // Retornar sucesso no processo pai
}

int	execute_pipeline(t_shell *cmd, char **envp)
{
	int		i;
	int		cmd_index = 0;
	char	**args;
	t_token *current_token = cmd->token;

	if (create_pipes(cmd) != 0)
		return (1);
	if (alloc_pids(cmd) != 0)
		return (1);
	for (i = 0; i < cmd->n_inputs; i++)
	{
		args = get_command_tokens(cmd, &cmd_index, &current_token);
		if (!args)
		{
			fprintf(stderr, "Error processing command tokens.\n");
			return (1);
		}
		if (execute_builtin(args, cmd))
		{
			free(args);
			continue;
		}
		if (execute_command(cmd, args, current_token, envp, i) != 0)
			return (1);
		free(args);
	}
	close_fds(cmd);
	return wait_for_child(cmd);
}
