/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:12:51 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/17 16:48:09 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		flag_R(t_truc *parse, char *path)
{
	DIR *dir;
	// DIR *dir2;
	char *caca;
	// struct dirent *dp;
	x_file *lsd;

	caca = malloc(2000);
	caca[0] = 0;
	ls_core(parse, path, &lsd);
	while (lsd)
	{
		if ((lsd->name[0] != '.' || lsd->name[1] != 0) && (lsd->name[1] != '.' || lsd->name[2] != 0))
		{
			caca = ft_strcat(caca, path);
			if (caca[ft_strlen(caca) - 1] != '/')
				ft_strcat(caca, "/");
			caca = ft_strcat(caca, lsd->name);
			if ((dir = opendir(caca)))
			{
				closedir(dir);
				write(1, "\n", 1);
				ft_printf("%s\n", caca);
				caca = ft_strcat(caca, "/");
				flag_R(parse, caca);
			}
			else if (errno == 13)
				ft_printf("\n%s:\nft_ls: %s: Permission denied\n", caca, lsd->name);
			caca[0] = 0;
		}
		lsd = lsd->next;
	}
	free(lsd);
	return (0);
}
