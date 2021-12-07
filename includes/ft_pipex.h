#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# define HEREDOC "here_doc"
# define HEREDOC_LEN 8
void	setupInput(char **av, int is_heredoc);
void	die(char *basename, char *file);
char	*get_cmd_path(char *cmd, char **env);

typedef struct s_data
{
	int	size;
	char **cmds;
	int fd_out;
	char **env;

}	t_data;
#endif
