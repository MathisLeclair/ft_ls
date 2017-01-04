/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 11:13:27 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	type(struct stat *buf)
{
	char ret;

	ret = '-';
	if (S_ISDIR(buf->st_mode) == 1)
		ret = 'd';
	else if (S_ISCHR(buf->st_mode) == 1)
		ret = 'c';
	else if (S_ISBLK(buf->st_mode) == 1)
		ret = 'b';
	else if (S_ISFIFO(buf->st_mode) == 1)
		ret = 'p';
	else if (S_ISLNK(buf->st_mode) == 1)
		ret = 'l';
	else if (S_ISSOCK(buf->st_mode) == 1)
		ret = 's';
	return (ret);
}

char	*droit(int mode, t_file *lsd)
{
	static char *str;

	str = malloc(12);
	ft_strcpy(str, "---------- \0");
	(mode & S_IRUSR) ? str[1] = 'r' : 0;
	(mode & S_IWUSR) ? str[2] = 'w' : 0;
	(mode & S_IXUSR) ? str[3] = 'x' : 0;
	(mode & S_IRGRP) ? str[4] = 'r' : 0;
	(mode & S_IWGRP) ? str[5] = 'w' : 0;
	(mode & S_IXGRP) ? str[6] = 'x' : 0;
	(mode & S_IROTH) ? str[7] = 'r' : 0;
	(mode & S_IWOTH) ? str[8] = 'w' : 0;
	(mode & S_IXOTH) ? str[9] = 'x' : 0;
	str[0] = lsd->type;
	return (str);
}

char	*ft_color(t_file *lsd, int i)
{
	if (i == 1)
	{
		if (lsd->type == 'd')
			return ("\e[0;36m");
		if (lsd->type == 'c')
			return ("\e[7;33m");
		if (lsd->type == 'b')
			return ("\e[0;32m");
		if (lsd->type == 'p')
			return ("\e[1;33m");
		if (lsd->type == 'l')
			return ("\e[0;35m");
		if (lsd->type == 's')
			return ("\e[0;32m");
	}
	return ("\e[0m");
}

void	lsd_null(t_file *lsd)
{
	lsd->acces = NULL;
	lsd->type = 0;
	lsd->nbf = 0;
	lsd->nbfconv = NULL;
	lsd->total = 0;
	lsd->group = NULL;
	lsd->size = 0;
	lsd->sizeconv = NULL;
	lsd->date = 0;
	lsd->name = NULL;
	lsd->path = NULL;
	lsd->next = NULL;
	lsd->prev = NULL;
	lsd->minor = 0;
	lsd->major = 0;
	lsd->owner = NULL;
}

void	ft_lstcreate2(t_file *lsd, struct stat *buf,
	struct passwd *test, char *path)
{
	dev_t toast;

	lsd->owner = ft_strdup(test->pw_name);
	lsd->size = buf->st_size;
	lsd->date = buf->st_mtime;
	lsd->nbf = buf->st_nlink;
	lsd->type = type(buf);
	lsd->acces = droit(buf->st_mode, lsd);
	lsd->path = ft_strdup(path);
	lsd->total = buf->st_blocks;
	if (lsd->type == 'c')
	{
		toast = buf->st_rdev;
		lsd->minor = toast % 256;
		lsd->major = toast;
	}
}

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
