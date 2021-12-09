/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:32:26 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/07 18:32:26 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ft_str.h"
#include "ft_pipex.h"

int	_exec(char *cmd, char **env)
{
	char	**args;
	char	*file;
	int		pid;

	args = ft_split(cmd, ' ');
	if (args == NULL)
		return (-1);
	file = get_cmd_path(args[0], env);
	if (file == NULL)
		return (-1);
	free(args[0]);
	args[0] = file;
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		execve(file, args, env);
		exit(0);
	}
	free_split(args);
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
	if ((fildes == NULL || pids == NULL)
		&& ft_free(fildes) && ft_free(pids))
		return (NULL);
	i = 0;
	while (i < data->size)
	{
		if ((handle_pipe(data, i, fildes) == -1)
			&& ft_free(fildes) && ft_free(pids))
			return (NULL);
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
	int	status;

	pids = execmap(data);
	if (pids == NULL)
		exit(1);
	i = 0;
	while (data->cmds[i - 1])
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
