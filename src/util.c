/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:21:46 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/08 16:21:46 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_pipex.h"

void	die(char *basename, char *file)
{
	show_errno(basename, file);
	exit(1);
}

int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

int	ft_dup2(int fd1, int fd2)
{
	int	res;
	
	res = dup2(fd1, fd2);
	close(fd1);
	return (res);
}

int	*ft_ialloc(int size, int defval)
{

	int	*mem;

	mem = (int *) malloc(sizeof(int) * size);
	while (size--)
	{
		mem[size] = defval;
	}
	return (mem);
}
