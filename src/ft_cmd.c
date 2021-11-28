#include <unistd.h>
#include <stdlib.h>
#include "ft_split.h"
#include "ft_str.h"

char **get_paths(char **env)
{
	int i;

	i = 0;
	while(env[i]) {
		if(ft_strncmp(env[i], "PATH=", 5))
			return ft_split(env[i] + 5, ':');
	}
	return 0;
}

char *get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char *filename;

	paths = get_paths(env);
	i = 0;
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd);
		if(access(filename, F_OK | X_OK) == 0)
			return filename;
		free(filename);
	}
	return 0;
}

char *exec_cmd(char *cmd, char *input, char **env)
{
	char **args;
	char 

	args = ft_split(cmd, ' ');

	get_cmd_path(args[0], env);
	
	
}
