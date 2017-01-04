/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:23:51 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 19:24:03 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_err(int i, char *tmp)
{
	if (i == -666)
		ft_printf("fts_open: No such file or directory\n");
	else if (i == -1)
		ft_printf("Illegal flag.\nusage: ./ls [-rRatTl]\n");
	else if (i == -10)
		ft_printf("Allocation error. Bitch.\n");
	else if (i == ENOTDIR && tmp[ft_strlen(tmp) - 1] != '/')
		ft_printf("%s\n", tmp);
	else
	{
		ft_printf("ft_ls: %s: ", tmp);
		perror(NULL);
		exit(-1);
	}
	exit(-1);
}
