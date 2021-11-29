/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:51:10 by iait-bel          #+#    #+#             */
/*   Updated: 2021/11/27 15:51:10 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "ft_error.h"
#include "ft_str.h"
#include <stdlib.h>


char *ft_read(char *path)
{
	int fd;

	fd =  open(path, O_RDONLY);
	if(fd == -1)
	{
		show_errno("pipex" , path);
	}
	return (char *) 0;
}
