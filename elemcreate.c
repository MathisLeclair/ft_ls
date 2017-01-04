#include "ls.h"

char	*ft_pathname(char *path, char *name)
{
	char	bool;
	int		i;
	int		j;
	char	*pathname;

	if (!(pathname = malloc(ft_strlen(path) + ft_strlen(name) + 2)))
		ft_err(-10, 0);
	i = -1;
	while (path[++i])
		pathname[i] = path[i];
	bool = 0;
	if (path[i - 1] != '/')
	{
		pathname[i] = '/';
		bool = 1;
	}
	j = -1;
	while (name[++j])
		pathname[i + j + bool] = name[j];
	pathname[i + j + bool] = 0;
	return (pathname);
}

void	ft_elemcreate2(t_file *lsd, struct stat *buf, char *path)
{
	dev_t			toast;
	struct passwd	*test;

	test = getpwuid(buf->st_uid);
	if (test)
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

t_file	*ft_elemcreate(struct dirent *dp, char *path)
{
	struct stat		*buf;
	struct group	*group;
	t_file			*lsd;
	char			*pathname;

	pathname = ft_pathname(path, dp->d_name);
	if (!(buf = malloc(sizeof(struct stat))))
		ft_err(-10, 0);
	if (!(lsd = malloc(sizeof(t_file))))
		ft_err(-10, 0);
	lsd_null(lsd);
	lsd->name = ft_strdup(dp->d_name);
	if (lstat(pathname, buf) == -1)
	{
		free(buf);
		free(pathname);
		return (lsd);
	}
	group = getgrgid(buf->st_gid);
	ft_elemcreate2(lsd, buf, path);
	if (group)
		lsd->group = ft_strdup(group->gr_name);
	free(buf);
	free(pathname);
	return (lsd);
}
