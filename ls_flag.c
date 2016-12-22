/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:12:51 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/22 18:49:03 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	flag_r2(DIR *dir, char *caca, t_truc *parse)
{
	closedir(dir);
	write(1, "\n", 1);
	ft_printf("%s:\n", caca);
	ft_strcat(caca, "/");
	flag_r(parse, caca);
}

void	flag_r(t_truc *parse, char *path)
{
	DIR		*dir;
	char	*caca;
	t_file	*lsd;

	caca = malloc(2000);
	caca[0] = 0;
	ls_core(parse, path, &lsd);
	while (lsd)
	{
		if ((lsd->name[0] != '.' || lsd->name[1] != 0) && (lsd->name[1] != '.' 
			|| lsd->name[2] != 0) && (lsd->name[0] != '.' || parse->flag_a))
		{
			ft_strcat(caca, path);
			if (caca[ft_strlen(caca) - 1] != '/')
				ft_strcat(caca, "/");
			ft_strcat(caca, lsd->name);
			if (lsd->type != 'l' && (dir = opendir(caca)))
				flag_r2(dir, caca, parse);
			else if (errno == 13)
				ft_printf("\n%s:\nft_ls: %s: Permission denied\n",
				caca, lsd->name);
			caca[0] = 0;
		}
		lsd = lsd->next;
	}
	free(lsd);
}
