/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/14 18:32:30 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_lstsort(t_truc *parse, t_file *lst, int i)
{
	int u;

	u = 0;
	if (parse->flag_t == 0 && parse->flag_r == 0)
	{
		while (u != i - 1)
		{
			printf("u = %d et i - 1 = %i\n", u, i - 1);
			u = 0;
			while (lst->next)
			{
				printf("Test\n");
				if(strcmp(lst->name, (lst->next)->name) > 0)
				{
					(lst->next)->prev = lst->prev;
					lst->next = (lst->next)->next;
					lst->prev = lst->next;
					(lst->next)->next = lst;
				}
				else
					lst = lst->next;
			}
			while (lst->prev)
			{
				if(strcmp(lst->name, (lst->prev)->name) > 0)
				{
					(lst->prev)->next = lst->next;
					lst->prev = (lst->prev)->prev;
					lst->next = lst->prev;
					(lst->prev)->prev = lst;
					++u;
				}
				lst = lst->prev;
			}
		}
	}
}

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
		// free(dp);
		while ((dp = readdir(dir)))
		{
			lst->next = ft_lstcreate(dp);
			(lst->next)->prev = *lsd;
			lst = lst->next;
			// free(dp);
			++i;
		}
		ft_lstsort(parse, *lsd, i);
	}
	//affichage
	while (*lsd)
	{
		if ((*lsd)->name[0] != '.'|| parse->flag_a == 1)
		{
			write(1, dp->d_name, ft_strlen(dp->d_name));
			write(1, "\n", 1);
		}
		*lsd = (*lsd)->next;
	}
	//fin affichage
	closedir(dir);
}