/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:44:10 by iait-bel          #+#    #+#             */
/*   Updated: 2021/11/27 15:44:10 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "ft_error.h"
#include "ft_cmd.h"
#include "ft_pipex.h"
#include "ft_str.h"

int	open_outfile(int ac, char **av, int is_heredoc)
{
	int	flags;

	flags = O_WRONLY | O_TRUNC | O_CREAT;
	if (is_heredoc)
	{
		flags |= O_APPEND;
		flags &= ~O_TRUNC;
	}
	return (open(av[ac - 1], flags, S_IRWXU));
}

void	die_if(int val, char *basename, char *file)
{
	if (val == 0)
		return ;
	die(basename, file);
	close(STDIN_FILENO);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		is_heredoc;

	if (ac < 4)
		return (1);
	is_heredoc = (ft_strncmp(av[1], HEREDOC, HEREDOC_LEN) == 0);
	setupInput(av, is_heredoc);
	data.fd_out = open_outfile(ac, av, is_heredoc);
	die_if(data.fd_out == -1, av[0], av[ac - 1]);
	data.env = env;
	data.size = ac - 3 - is_heredoc;
	data.cmds = av + 2 + is_heredoc;
	av[ac - 1] = 0;
	exec_cmd(&data);
	close(data.fd_out);
	close(STDIN_FILENO);
	return (0);
}
