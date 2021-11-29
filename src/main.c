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

int main (int argc, char *argv[], char **env)
{
	int fd;

	if(argc == 0)
		return 0;
	fd =  open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		show_errno("pipex" , argv[1]);
	}
	fd = exec_cmd(argv[2], fd, env);
	//cmd2_content = exec_cmd(argv[3], cmd1_content);
	//ft_write(argv[4], cmd2_content);
	//free(file1_content);
	return 0;
}
