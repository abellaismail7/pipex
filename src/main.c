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
#include "ft_read.h"

int main (int argc, char *argv[])
{
	char *file1_content;
	//char *cmd1_content;
	//char *cmd2_content;
	int size;

	file1_content = ft_read(argv[1], &size);
	//cmd1_content = exec_cmd(argv[2], file1_content);
	//cmd2_content = exec_cmd(argv[3], cmd1_content);
	//ft_write(argv[4], cmd2_content);
	write(1, file1_content, size);
	free(file1_content);
	return 0;
}
