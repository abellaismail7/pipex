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

int main (int ac, char **av, char **env)
{
	int fd_in;
	int fd_out;

	if(ac < 4)
		return 0;
	fd_in =  open(av[1], O_RDONLY);
	fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT);
	av[ac - 1] = 0;
	if(fd_in == -1 || fd_out == -1)
	{
		show_errno("pipex" , av[0]);
	}
	exec_cmd(av + 2, fd_in, env);
	close(fd_in);
	close(fd_out);
	return 0;
}
