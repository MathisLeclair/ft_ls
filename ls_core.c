/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/16 18:24:46 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"


char	type(struct stat *buf)
{
	char ret;

	ret = 'k';
	if (S_ISREG(buf->st_mode) == 1)
		ret = '-';
	else if (S_ISDIR(buf->st_mode) == 1)
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
	char *str;

	str = malloc(11);
	str = "----------\0";
	(mode & S_IRUSR) ? str[1] = 'r' : (void)str;
	(mode & S_IWUSR) ? str[2] = 'w' : (void)str;
	(mode & S_IXUSR) ? str[3] = 'x' : (void)str;
	if (mode & S_ISUID)
		str[3] = ((mode & S_IXUSR) ? 's' : 'S');
	(mode & S_IRGRP) ? str[4] = 'r' : (void)str;
	(mode & S_IWGRP) ? str[5] = 'w' : (void)str;
	(mode & S_IXGRP) ? str[6] = 'x' : (void)str;
	if (mode & S_ISGID)
		str[6] = ((mode & S_IXGRP) ? 's' : 'S');
	(mode & S_IROTH) ? str[7] = 'r' : (void)str;
	(mode & S_IWOTH) ? str[8] = 'w' : (void)str;
	(mode & S_IXOTH) ? str[9] = 'x' : (void)str;
	if (mode & S_ISVTX)
		str[9] = ((str[9] == '-') ? 'T' : 't');
	str[0] = lsd->type;
	return (str);
}

t_file	*ft_lstcreate(struct dirent *dp, char *path)
{	
	struct stat *buf;
	struct group *group;
	struct passwd *test; 
	t_file *lsd;
	char *pathname;

	pathname = ft_strjoin(path, dp->d_name);
	buf = malloc(sizeof(struct stat));
	group = malloc(sizeof(struct passwd));
	lsd = malloc(sizeof(t_file));
	lsd->name = ft_strdup(dp->d_name);
	stat(pathname, buf);
	group = getgrgid(buf->st_gid);
	test = getpwuid(buf->st_uid);
	lsd->owner = test->pw_name;
	lsd->size = buf->st_size;
	lsd->group = group->gr_name;
	lsd->date = buf->st_atime;
	lsd->type = type(buf);
	lsd->acces = droit(buf->st_mode, lsd);
	lsd->next = NULL;
	lsd->prev = NULL;
	return (lsd);
}

void	ls_core(t_truc *parse, char *path, t_file **lsd)
{
	DIR *dir;
	struct dirent *dp;
	t_file *lst;
	int i;

	dir = opendir(path);
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
		(*lsd)->nbf = i;
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