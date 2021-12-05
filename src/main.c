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
#include<unistd.h>
#include<fcntl.h>
#include "ft_error.h"
#include "ft_cmd.h"
#include "ft_pipex.h"
#include "ft_str.h"

int	openOutFile(int ac, char **av, int is_heredoc)
{
	int flags;

	flags = O_WRONLY | O_TRUNC | O_CREAT;
	if (is_heredoc)
	{
		flags |= O_APPEND; 
		flags &= ~O_TRUNC;
	}
	return open(av[ac - 1], flags);
}

void dieIf(int val, char *basename, char *file)
{
	if(val == 0)
		return ;
	die(basename, file);
	close(STDIN_FILENO);
}

int main (int ac, char **av, char **env)
{
	t_data data;
	int is_heredoc;

	if(ac < 4)
		return 1;
	is_heredoc = (ft_strncmp(av[1],"heredoc", 7) == 0);
	setupInput(av, is_heredoc);
	data.fd_out = openOutFile(ac, av, is_heredoc);
	dieIf(data.fd_out == -1, av[0], av[ac - 1]);
	data.env 	= env;
	data.size	= ac - 3 - is_heredoc;
	data.cmds 	= av + 2 + is_heredoc;
	av[ac - 1] = 0;
	exec_cmd(&data);
	close(data.fd_out);
	close(STDIN_FILENO);
	return 0;
}
