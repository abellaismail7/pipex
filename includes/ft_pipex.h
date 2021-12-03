#ifndef FT_PIPEX_H
# define FT_PIPEX_H

typedef struct s_data
{
	int	size;
	char **cmds;
	int fd_in;
	int fd_out;
	char **env;
}	t_data;
#endif
