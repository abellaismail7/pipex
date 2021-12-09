/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:14:31 by iait-bel          #+#    #+#             */
/*   Updated: 2021/11/27 16:14:31 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

int				ft_strlen(char *str);
int				ft_strncmp(char *s1, char *s2, int n);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(char *src);
void			ft_putstr(int fd, char *str);
char			**ft_split(char *str, char c);
void			free_split(char **result);

#endif
