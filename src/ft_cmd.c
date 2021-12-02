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

int _exec(char *cmd, int *fds, char **env)
{
	char **args;
	char *file;
	int pid;
	int state;
	
	fds = fds + 1;
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
		state = execve(file, args, env);
		exit(state != -1);
	}
	return pid;
}

int *fdsmap(char **cmd)
{
	int i;
	int *res;
	i = 0;
	while (cmd[i])
		i++;
	res = malloc(sizeof(int *) * (i * 2));
	return res;
}

int	*execmap(char **cmds, int fd, char **env)
{
	int i;
	int count;
	int *fildes;
	int *pids;
	
	count = 0;
	while(cmds[count])
		count++;

	fildes = fdsmap(cmds);
	pids = malloc(sizeof(int *) * count);
	dup2(fd, STDIN_FILENO);
	close(fd);
	i = 0;
	while(cmds[i])
	{
		pipe(fildes);
		dup2(fildes[1], STDOUT_FILENO);
		close(fildes[1]);
		if (cmds[i + 1] == 0)
		{
			dup2(4, STDOUT_FILENO);
			close(4);
		}
		if(i != 0)
		{
			dup2(*(fildes - 2), STDIN_FILENO);
			close(*(fildes - 2));
		}
		pids[i] = _exec(cmds[i], fildes, env);
		fildes += 2;
		i++;
	}
	return pids;
}



int exec_cmd(char **cmds, int fd, char **env)
{
	int *pids;
	int i;

	pids = execmap(cmds, fd, env);

	i = 0;
	while(cmds[i])
		waitpid(pids[i++], NULL, 0);

	return 0;
}
