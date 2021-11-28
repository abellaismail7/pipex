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


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*_dst;
	const char		*_src;
	unsigned int	i;

	if (dst == 0 && src == 0)
		return (0);
	_dst = dst;
	_src = src;
	i = 0;
	while (i < n)
	{
		_dst[i] = _src[i];
		i++;
	}
	return (dst);
}

char	*ft_memjoin(void *s1, void *s2, int len1, int len2)
{
	char	*str;

	str = malloc(len1 + len2 + 1);
	if (str)
	{
		ft_memcpy(str, s1, len1);
		ft_memcpy(str + len1, s2, len2);
	}
	free(s1);
	return (str);
}

char *read_file(int fd, int *size)

{
	char	*str;
	char	*buf;
	int		n;

	str = 0;
	buf = (char *) malloc(1024);
	if(buf == 0)
		return 0;
	*size = 0;
	while(1)
	{
		n = read(fd, buf, 1024);
		if(*size > 1)
			break;
		str = ft_memjoin(str, buf, *size, n);
		if(str == 0)
			break ;
		*size += n;
	}
	free(buf);
	return str;
}

char *ft_read(char *path, int *size)
{
	int fd;

	fd =  open(path, O_RDONLY);
	if(fd == -1)
	{
		show_errno("pipex" , path);
	}
	return read_file(fd, size);
}
