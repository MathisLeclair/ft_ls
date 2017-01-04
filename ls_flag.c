/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:12:51 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 14:39:00 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	flag_r2(DIR *dir, char *caca, t_truc *parse)
{
	closedir(dir);
	write(1, "\n", 1);
	ft_printf("%s:\n", caca);
	flag_rr(parse, caca);
}

void	flag_rr(t_truc *parse, char *path)
{
	char	*caca;
	t_file	*lsd;
	t_file	*sav;
	DIR		*dir;

	ls_core(parse, path, &lsd);
	sav = lsd;
	while (lsd)
	{
		if ((lsd->name[0] != '.' || lsd->name[1] != 0) && (lsd->name[1] != '.'
			|| lsd->name[2] != 0) && (lsd->name[0] != '.' || parse->flag_a))
		{
			caca = ft_pathname(path, lsd->name);
			if (lsd->type != 'l' && (dir = opendir(caca)))
				flag_r2(dir, caca, parse);
			else if (errno == 13)
				ft_printf("\n%s:\nft_ls: %s: Permission denied\n",
				caca, lsd->name);
			free(caca);
		}
		lsd = lsd->next;
	}
	list_free(sav);
}
