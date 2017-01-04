/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 11:46:42 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file	*ft_lstcreate(struct dirent *dp, char *path)
{
	struct stat		*buf;
	struct group	*group;
	struct passwd	*test;
	t_file			*lsd;
	char			*pathname;

	pathname = ft_strjoin(path, dp->d_name);
	buf = malloc(sizeof(struct stat));
	lsd = malloc(sizeof(t_file));
	lsd_null(lsd);
	lsd->name = ft_strdup(dp->d_name);
	if (lstat(pathname, buf) == -1)
	{
		free(buf);
		return (lsd);
	}
	group = getgrgid(buf->st_gid);
	test = getpwuid(buf->st_uid);
	ft_lstcreate2(lsd, buf, test, path);
	lsd->group = ft_strdup(group->gr_name);
	free(buf);
	free(pathname);
	return (lsd);
}

int		ft_lst(struct dirent *dp, t_file *lst, DIR *dir, char *path)
{
	int i;

	i = 1;
	while ((dp = readdir(dir)))
	{
		lst->next = ft_lstcreate(dp, path);
		(lst->next)->prev = lst;
		lst = lst->next;
		++i;
	}
	return (i);
}

void	ls_core_to_long(t_truc *parse, t_file **lsd)
{
	if (((*lsd)->name[0] != '.' || parse->flag_a == 1))
		ft_printf("%s%s%s\n", ft_color((*lsd), 1), (*lsd)->name,
		ft_color((*lsd), 0));
	while ((*lsd)->next && ((*lsd) = (*lsd)->next))
		if (((*lsd)->next) && ((*lsd)->name[0] != '.' ||
		parse->flag_a == 1))
			ft_printf("%s%s%s\n", ft_color((*lsd), 1),
			(*lsd)->name, ft_color((*lsd), 0));
	if (((*lsd)->name[0] != '.' || parse->flag_a == 1))
		ft_printf("%s%s%s\n", ft_color((*lsd), 1), (*lsd)->name,
		ft_color((*lsd), 0));
	while ((*lsd)->prev)
		(*lsd) = (*lsd)->prev;
}

void	ls_core(t_truc *parse, char *path, t_file **lsd)
{
	DIR				*dir;
	struct dirent	*dp;

	path = ft_strjoin(path, (path[ft_strlen(path) - 1] != '/' ? "/" : ""));
	dir = opendir(path);
	if (!dir && ft_err(errno, path))
		return ;
	if ((dp = readdir(dir)))
	{
		*lsd = ft_lstcreate(dp, path);
		ft_lstsort(parse, *lsd, ft_lst(dp, *lsd, dir, path));
		while ((*lsd)->prev)
			(*lsd) = (*lsd)->prev;
		if (parse->flag_l == 0)
			ls_core_to_long(parse, lsd);
		else
			parse->flag_r ? print_l_reverse((*lsd), parse) :
			print_l((*lsd), parse);
	}
	while ((*lsd)->prev && !parse->flag_r && parse->flag_rr)
		*lsd = (*lsd)->prev;
	closedir(dir);
	free(path);
}
