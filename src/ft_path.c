#include "ft_str.h"
#include <unistd.h>
#include <stdlib.h>

char	**get_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (0);
}

char *checkRelativePath(char *cmd)
{
	if(cmd[0] == '.' && access(cmd, F_OK | X_OK) == 0)
		return ft_strdup(cmd);
	return NULL;
}

char *checkEnvPath(char *cmd, char **paths)
{
	char *filename;
	int i;

	i = 0;
	filename = NULL;
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd);
		if(access(filename, F_OK | X_OK) == 0)
			break ;
		free(filename);
		filename = NULL;
		i++;
	}
	return filename;
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*filename;

	filename = checkRelativePath(cmd);
	if (filename == NULL)
	{
		paths = get_paths(env);
		filename = checkEnvPath(cmd, paths);
		free(paths);
	}
	if (filename == NULL)
	{
		ft_putstr(2, "pipex: command not found: ");
		ft_putstr(2, cmd);
		ft_putstr(2, "\n");
	}
	return (filename);
}
