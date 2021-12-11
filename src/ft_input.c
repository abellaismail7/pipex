/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:27:26 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/08 16:27:26 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_cmd.h"
#include "ft_pipex.h"
#include "ft_str.h"

void	ft_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

int	readfromkeyboard(char *until)
{
	int		fildes[2];
	int		u_len;
	int		n;
	char	*buf;

	u_len = ft_strlen(until);
	if (pipe(fildes) == -1)
		return (-1);
	buf = malloc(sizeof(char *) * (u_len + 1));
	if (buf == NULL)
		return (-1);
	ft_putstr(1, "heredoc> ");
	while (1)
	{
		n = read(STDIN_FILENO, buf, u_len);
		if (n == -1 || (n == u_len && ft_strncmp(buf, until, n) == 0))
			break ;
		write(fildes[1], buf, n);
		if (n != 0 && buf[n - 1] == '\n')
			ft_putstr(1, "heredoc> ");
	}
	free(buf);
	close(fildes[1]);
	return (fildes[0]);
}

void	fake_input(int is_heredoc)
{
	int	fildes[2];

	if (is_heredoc || pipe(fildes) == -1)
		exit(1);
	if (dup2(fildes[0], STDIN_FILENO) == -1)
		exit(1);
	close(fildes[0]);
	close(fildes[1]);
}

void	setupinput(char **av, int is_heredoc)
{
	int	fd_in;

	if (is_heredoc)
		fd_in = readfromkeyboard(av[2]);
	else
		fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
	{
		show_errno(av[0], av[1]);
		fake_input(is_heredoc);
	}
	else
		ft_dup2(fd_in, STDIN_FILENO);
}
