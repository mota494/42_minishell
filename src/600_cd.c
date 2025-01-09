/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:41:58 by mloureir          #+#    #+#             */
/*   Updated: 2025/01/09 11:31:12 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_dir_to(char *foldername, t_shell *cmd)
{
	char	*folder;
	char	buffer[PATH_MAX];

	folder = get_env(foldername);
	if (!folder)
	{
		printf("Minishell: cd: OLDPWD is not set");
		cmd->error_code = 1;
	}
	else
	{
		chdir(get_env("OLDPWD"));
		printf("%s\n", get_env("OLDPWD"));
		cmd->error_code = 0;
		if (get_env("PWD"))
			change_env_value("PWD", getcwd(buffer, PATH_MAX));
		else
			add_env_value("PWD", getcwd(buffer, PATH_MAX), 0);
		if (get_env("OLDPWD"))
			change_env_value("OLDPWD", cmd->curdir);
		else
			add_env_value("OLDPWD", cmd->curdir, 0);
		free(cmd->curdir);
		cmd->curdir = alocpy(getcwd(buffer, PATH_MAX));
	}
}

void	cd_empty_args(t_shell *cmd)
{
	char	buffer[PATH_MAX];

	cmd->error_code = 0;
	if (get_env("HOME"))
	{
		chdir(get_env("HOME"));
		cmd->error_code = 0;
		if (get_env("PWD"))
			change_env_value("PWD", getcwd(buffer, PATH_MAX));
		else
			add_env_value("PWD", getcwd(buffer, PATH_MAX), 0);
		if (get_env("OLDPWD"))
			change_env_value("OLDPWD", cmd->curdir);
		else
			add_env_value("OLDPWD", cmd->curdir, 0);
		free(cmd->curdir);
		cmd->curdir = alocpy(getcwd(buffer, PATH_MAX));
	}
	else
	{
		printf("Minishell: cd: HOME is not set");
		cmd->error_code = 1;
	}
}

void	cd_change_dir(t_shell *cmd)
{
	char	buffer[PATH_MAX];

	cmd->error_code = 0;
	if (!getcwd(buffer, PATH_MAX))
		return ;
	if (get_env("PWD"))
		change_env_value("PWD", getcwd(buffer, PATH_MAX));
	else
		cmd->c_envp = add_env_value("PWD", getcwd(buffer, PATH_MAX), 0);
	if (get_env("OLDPWD"))
		change_env_value("OLDPWD", cmd->curdir);
	else
		cmd->c_envp = add_env_value("OLDPWD", cmd->curdir, 0);
	free(cmd->curdir);
	cmd->curdir = alocpy(getcwd(buffer, PATH_MAX));
}

int	check_for_cd_flags(t_token *arg)
{
	if (arg->cmd_line[0] == '-')
	{
		if (arg->cmd_line[1] == '-')
		{
			if (arg->cmd_line[2] == '\0')
				return (1);
			else
			{
				ft_printf(2, "minishell: cd: -%c invalid option\n",
					arg->cmd_line[1]);
				return (0);
			}
		}
		if (arg->cmd_line[1] != '\0')
		{
			ft_printf(2, "minishell: cd: -%c invalid option\n",
				arg->cmd_line[1]);
			return (0);
		}
	}
	return (1);
}

void	cd(t_shell *cmd)
{
	t_token	*temp;

	temp = cmd->token;
	temp = temp->next;
	if (count_args(temp) > 1)
	{
		printf("minishell: cd: too many arguments\n");
		cmd->error_code = 1;
	}
	if (count_args(temp) == 0 || sstrcmp(temp->cmd_line, "--"))
		cd_empty_args(cmd);
	else if (!check_for_cd_flags(temp))
		cmd->error_code = 2;
	else if (sstrcmp(temp->cmd_line, "-"))
		change_dir_to("OLDPWD", cmd);
	else if ((chdir(temp->cmd_line) == -1))
	{
		printf("minishell: cd: %s:No such file or directory\n",
			temp->cmd_line);
		cmd->error_code = 1;
	}
	else
		cd_change_dir(cmd);
}
