/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:38:05 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/08 16:38:05 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# define HEREDOC "here_doc"
# define HEREDOC_LEN 8

void	setupinput(char **av, int is_heredoc);
void	die(char *basename, char *file);
char	*get_cmd_path(char *cmd, char **env);
int		show_errno(char *basename, char *filename);

typedef struct s_data
{
	int		size;
	char	**cmds;
	int		fd_out;
	char	**env;

}	t_data;

#endif
