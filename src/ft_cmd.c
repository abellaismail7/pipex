#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ft_split.h"
#include "ft_str.h"
#include "ft_pipex.h"

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

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char	*filename;

	paths = get_paths(env);
	i = 0;
	filename = 0;
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd);
		if(access(filename, F_OK | X_OK) == 0)
			break ;
		free(filename);
		i++;
	}
	free(paths);
	return (filename);
}

int	_exec(char *cmd, int *fds, char **env)
{
	char	**args;
	char	*file;
	int		pid;
	int		state;

	fds = fds + 1;
	args = ft_split(cmd, ' ');
	file = get_cmd_path(args[0], env);
	free(args[0]);
	args[0] = file;
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		state = execve(file, args, env);
		free(args);
		exit(state != -1);
	}
	return (pid);
}

int	handle_pipe(t_data *data, int index, int *fildes)
{
	if (pipe(fildes) == -1)
		return (-1);
	if (dup2(fildes[1], STDOUT_FILENO) == -1)
		return (-1);
	close(fildes[1]);
	if (index + 1 == data->size)
	{
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(data->fd_out);
	}
	if (index != 0)
	{
		if (dup2(*(fildes - 2), STDIN_FILENO) == -1)
			return (-1);
		close(*(fildes - 2));
	}
	return (0);
}

int	*execmap(t_data *data)
{
	int	i;
	int	*fildes;
	int	*pids;

	fildes = malloc(sizeof(int *) * (data->size * 2));
	pids = malloc(sizeof(int *) * data->size);
	if (fildes == NULL || pids == NULL)
	{
		free(fildes);
		free(pids);
		return (NULL);
	}
	i = 0;
	while (data->cmds[i])
	{
		handle_pipe(data, i, fildes);
		pids[i] = _exec(data->cmds[i], fildes, data->env);
		fildes += 2;
		i++;
	}
	return (pids);
}

int	exec_cmd(t_data *data)
{
	int	*pids;
	int	i;

	pids = execmap(data);
	if(pids == NULL)
		return (1);
	i = 0;
	while(data->cmds[i])
		waitpid(pids[i++], NULL, 0);
	free(pids);
	return (0);
}
