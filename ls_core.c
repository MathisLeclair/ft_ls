/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/21 16:33:55 by mleclair         ###   ########.fr       */
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
			return("\e[0;36m");
		if (lsd->type == 'c')
			return("\e[7;33m");
		if (lsd->type == 'b')
			return("\e[0;32m");
		if (lsd->type == 'p')
			return("\e[1;33m");
		if (lsd->type == 'l')
			return("\e[0;35m");
		if (lsd->type == 's')
			return("\e[0;32m");
	}
	return("\e[0m");
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
	lsd->name = NULL;
	lsd->date = 0;
	lsd->path = NULL;
	lsd->next = NULL;
	lsd->prev = NULL;
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
	lstat(pathname, buf);
	group = getgrgid(buf->st_gid);
	test = getpwuid(buf->st_uid);
	lsd_null(lsd);
	lsd->owner = ft_strdup(test->pw_name);
	lsd->size = buf->st_size;
	lsd->group = ft_strdup(group->gr_name);
	lsd->date = buf->st_mtime;
	lsd->nbf = buf->st_nlink;
	lsd->type = type(buf);
	lsd->name = ft_strdup(dp->d_name);
	lsd->acces = droit(buf->st_mode, lsd);
	lsd->path = ft_strdup(path);
	lsd->total = buf->st_blocks;
	return (lsd);
}

void	ls_core(t_truc *parse, char *path, t_file **lsd)
{
	DIR				*dir;
	struct dirent	*dp;
	t_file			*lst;
	int				i;
	char			*tmp;

	tmp = path;
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	dir = opendir(path);
	if (!dir)
	{
		ft_err(errno, tmp);
		return ;
	}
	if ((dp = readdir(dir)))
	{
		i = 1;
		*lsd = ft_lstcreate(dp, path);
		lst = *lsd;
		while ((dp = readdir(dir)))
		{
			lst->next = ft_lstcreate(dp, path);
			(lst->next)->prev = lst;
			lst = lst->next;
			++i;
		}
		lst = *lsd;
		ft_lstsort(parse, *lsd, i);
		while (lst->prev)
			lst = lst->prev;
		if (parse->flag_l == 0)
		{
			while (lst->next)
			{
				if (parse->flag_r == 0 && (lst->name[0] != '.' || parse->flag_a == 1))
					ft_printf("%s%s%s\n",ft_color(lst, 1), lst->name, ft_color(lst, 0));
				lst = lst->next;
			}
			if ((lst->name[0] != '.' || parse->flag_a == 1))
				ft_printf("%s%s%s\n", ft_color(lst, 1), lst->name, ft_color(lst, 0));
			while (parse->flag_r && lst->prev)
			{
				if (lst->prev->name[0] != '.' || parse->flag_a == 1)
					ft_printf("%s\n", lst->prev->name);
				lst = lst->prev;
			}
		}
		else
			print_l(lst, parse);
		if (!(parse->flag_rr))
			list_free(lst);
	}
	closedir(dir);
}
