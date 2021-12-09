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
