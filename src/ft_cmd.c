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

int	_exec(char *cmd, char **env)
{
	char	**args;
	char	*file;
	int		pid;
	int		state;

	args = ft_split(cmd, ' ');
	file = get_cmd_path(args[0], env);
	if(file == NULL)
		return -1;
	free(args[0]);
	args[0] = file;
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		state = execve(file, args, env);
		free(args);
		exit(state != -1);
	}
	free(args);
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
		if (handle_pipe(data, i, fildes) == -1)
		{
			free(fildes);
			free(pids);
			return (NULL);
		}
		pids[i] = _exec(data->cmds[i], data->env);
		fildes += 2;
		i++;
	}
	return (pids);
}

int	exec_cmd(t_data *data)
{
	int	*pids;
	int	i;
	int status;

	pids = execmap(data);
	if(pids == NULL)
		exit(1);
	i = 0;
	while(data->cmds[i])
		waitpid(pids[i++], &status, 0);
	if (pids[data->size - 1] == -1)
		status = 127;
	else if (!WIFEXITED(status))
		status = 0;
	else
		status = WEXITSTATUS(status);	
	free(pids);
	exit(status);
	return (0);
}
