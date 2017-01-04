/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:23:51 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 19:12:20 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_err(int i, char *tmp)
{
	if (i == -1)
	{
		ft_printf("Illegal flag.\nusage: ./ls [-rRatTl]\n");
		exit(-1);
	}
	else if (i == -10)
	{
		ft_printf("Allocation error. Bitch.\n");
		exit(-2);
	}
	else if (i == ENOTDIR && tmp[ft_strlen(tmp) - 1] != '/')
	{
		printf("%s\n", tmp);
		exit(0);
	}
	else
	{
		ft_printf("ft_ls: %s: ", tmp);
		perror(NULL);
		exit(0);
	}
	return (1);
}
