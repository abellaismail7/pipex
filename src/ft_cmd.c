#include <unistd.h>
#include <stdlib.h>
#include "ft_split.h"
#include "ft_str.h"

char **get_paths(char **env)
{
	int i;

	i = 0;
	while(env[i]) {
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
			return ft_split(env[i] + 5, ':');
		i++;
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
	filename = 0;
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd);
		if(access(filename, F_OK | X_OK) == 0)
			break;
		free(filename);
		i++;
	}
	free(paths);
	return filename;
}

int exec_cmd(char *cmd, int fd, char **env)
{
	char **args;
	char *file;
	int state;

	args = ft_split(cmd, ' ');
	file = get_cmd_path(args[0], env);
	free(args[0]);
	args[0] = file;
	int pid = fork();
	if (pid == -1)
	{
		
		return 0;
	}
	dup2(fd, STDIN_FILENO);
	pipe(1, STDIN_FILENO);
	state = execve(file, args, env);
	if (state == -1)
	{
		
		return 0;
	}
	
	


	return 0;
}
