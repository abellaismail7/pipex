#ifndef FT_PIPEX_H
# define FT_PIPEX_H

void	setupInput(char **av, int is_heredoc);
void	die(char *basename, char *file);

typedef struct s_data
{
	int	size;
	char **cmds;
	int fd_out;
	char **env;

}	t_data;
#endif
