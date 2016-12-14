/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/14 20:30:01 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"


t_file	*ft_lstcreate(struct dirent *dp)
{
	t_file *lsd;

	lsd = malloc(sizeof(t_file));
	lsd->name = ft_strdup(dp->d_name);
	// blablabla
	lsd->next = NULL;
	lsd->prev = NULL;
	return (lsd);
}

void	ls_core(t_truc *parse, char *path, t_file **lsd)
{
	struct stat *buf;
	DIR *dir;
	struct dirent *dp;
	t_file *lst;
	int i;

	buf = malloc(sizeof(struct stat));
	dir = opendir(path);
	if ((dp = readdir(dir)))
	{
		i = 1;
		*lsd = ft_lstcreate(dp);
		lst = *lsd;
		while ((dp = readdir(dir)))
		{
			lst->next = ft_lstcreate(dp);
			(lst->next)->prev = lst;
			lst = lst->next;
			++i;
		}
		lst = *lsd;
		ft_lstsort(parse, *lsd, i);
		while (lst)
		{
			if (lst->name[0] != '.'|| parse->flag_a == 1)
			{
				write(1, lst->name, ft_strlen(lst->name));
				write(1, "\n", 1);
			}
			lst = lst->next;
		}
	}
	closedir(dir);
}