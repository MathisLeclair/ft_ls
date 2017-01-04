/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:23:51 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 17:24:07 by mleclair         ###   ########.fr       */
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
	else if (errno == ENOTDIR)
		ft_printf("%s\n", tmp);
	else
	{
		ft_printf("ft_ls: %s: ", tmp);
		perror(NULL);
		exit(0);
	}
	return (1);
}
