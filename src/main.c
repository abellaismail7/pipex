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

char	die(char *basename, char *file)
{
	show_errno(basename, file);
	exit(1);
}


int main (int ac, char **av, char **env)
{
	t_data data;

	if(ac < 4)
		return 0;
	if (av[1] == )
	data.fd_in = open(av[1], O_RDONLY);
	if (data.fd_in == -1)
		die(av[0], av[1]);
	data.fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT);
	if (data.fd_out == -1)
		die(av[0], av[1]);
	av[ac - 1] = 0;
	data.size	= ac - 3;
	data.env 	= env;
	data.cmds 	= av + 2;
	exec_cmd(&data);
	close(data.fd_in);
	close(data.fd_out);
	return 0;
}
