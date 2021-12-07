#include <stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include "ft_error.h"
#include "ft_cmd.h"
#include "ft_pipex.h"
#include "ft_str.h"


int	readfromkeyboard(char *until)
{
	int fildes[2];
	int u_len;
	int n;
	char *buf;

	u_len = ft_strlen(until);
	if(pipe(fildes) == -1)
		return -1;
	buf = malloc(sizeof(char *) * (u_len + 1));
	if(buf == NULL)
		return -1;
	ft_putstr(1, "heredoc> ");
	while(1)
	{
		n = read(STDIN_FILENO, buf, u_len); // protection
		if (n == u_len && ft_strncmp(buf,until, n) == 0)
			break ;
		write(fildes[1], buf, n);
		if(n != 0 && buf[n - 1] == '\n')
			ft_putstr(1, "heredoc> ");
	}
	free(buf);
	close(fildes[1]);
	return fildes[0];
}

void setupInput(char **av, int is_heredoc)
{
	int fd_in;

	if (is_heredoc)
		fd_in = readfromkeyboard(av[2]);
	else
		fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		die(av[0], av[1]);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}
