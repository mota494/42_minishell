#include "../minishell.h"

void	jump_spaces(char *line)
{
	while (*line == 32)
		line++;
}

t_types	get_type(char *cmd)
{
	printf("%s", cmd);
	return (error);
}

char	*strjchr(char *str, char c)
{
	char	*newstr;
	size_t	i;

	newstr = malloc(ft_strlen(str) + sizeof(char) + 1);
	i = 0;
	while (i < ft_strlen(str))
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	free(str);
	return (newstr);
}

char	*get_cmd(char *line)
{
	char	*toret;
	int		i;

	i = 0;
	toret = ft_calloc(1 ,1);
	if (line[i] == 34)
	{
		while (line[i++] != 34 && line[i])
		{
			toret = strjchr(toret, line[i]);
			i++;
		}
	}
	else
	{
		while (ft_ispace(line[i]) == 0 && line[i])
		{
			toret = strjchr(toret, line[i]);
			i++;
		}
	}
	return (toret);
}

void	treat_line(char *line, t_shell *cmd)
{
	jump_spaces(line);
	cmd->token = add_node(get_cmd(line));
	printf("%s", cmd->token->cmd_line);
}
