#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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


int _exec(char *cmd, int *fds, int fd_to, char **env)
{
	char **args;
	char *file;
	int pid;
	int state;

	args = ft_split(cmd, ' ');
	file = get_cmd_path(args[0], env);
	free(args[0]);
	args[0] = file;
	pid = fork();
	if (pid == -1)
	{
		return 0;
	}
	else if(pid == 0)
	{
		dup2(fds[fd_to], fd_to);
		close(fds[0]);
		close(fds[1]);
		state = execve(file, args, env);
		exit(state != -1);
	}
	return pid;
}

int exec_cmd(char **cmds, int fd, char **env)
{
	int fildes[2];
	int pid1;
	int pid2;
	int i;

	if(pipe(fildes) == -1)
	{
		
		return 0;
	}

	dup2(fd, STDIN_FILENO);
	i = 0;
	pid1 = _exec(cmds[i], fildes, STDOUT_FILENO, env);
	while(cmds[i] && cmds[i + 1])
	{
		pid2 = _exec(cmds[i + 1], fildes, STDIN_FILENO, env);
		if (cmds[i + 1] == 0)
		{
			dup2(4, STDOUT_FILENO);
		}
		i++;
	}
	close(fildes[0]);
	close(fildes[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}
