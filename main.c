/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 18:01:36 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file	*ft_start(char *path)
{
	struct stat		*buf;
	struct group	*group;
	t_file			*lsd;

	if (!(buf = malloc(sizeof(struct stat))))
		ft_err(-10, 0);
	if (!(lsd = malloc(sizeof(t_file))))
		ft_err(-10, 0);
	lsd_null(lsd);
	if (lstat(path, buf) == -1)
	{
		free(buf);
		return (lsd);
	}
	group = getgrgid(buf->st_gid);
	ft_elemcreate2(lsd, buf, path, path);
	if (group)
		lsd->group = ft_strdup(group->gr_name);
	lsd->name = ft_strdup(path);
	free(buf);
	return (lsd);
}

void	ls_ls(t_truc *machin, char *str)
{
	t_file	*lsd;
	char	*time;

	lsd = ft_start(str);
	lst_l_prepare(lsd, machin, 0);
	if (lsd->type == 'l' && machin->flag_l == 1)
	{
		free(lsd->path);
		lsd->path = "";
		linkatt(lsd);
		time = conv_time(lsd->date, machin);
		printf("%s %s %s %s %s %s %s%s%s\n", lsd->acces, lsd->sizeconv,
		lsd->owner, lsd->group, lsd->nbfconv, time, ft_color(lsd, 1),
		lsd->name, ft_color(lsd, 0));
		free(time);
		exit(1);
	}
	list_free(lsd);
	if (machin->flag_rr == 1)
		flag_rr(machin, str);
	else
	{
		ls_core(machin, str, &lsd);
		list_free(lsd);
	}
}

void	ft_initparse(t_truc *machin)
{
	machin->flag_rr = 0;
	machin->flag_r = 0;
	machin->flag_t = 0;
	machin->flag_tt = 0;
	machin->flag_a = 0;
	machin->flag_l = 0;
}

void	parse_flag(char *av, int u, t_truc *truc)
{
	while (av[u])
	{
		truc->flag_rr = ((av[u] == 'R') || truc->flag_rr) ? 1 : 0;
		truc->flag_r = ((av[u] == 'r') || truc->flag_r) ? 1 : 0;
		truc->flag_l = ((av[u] == 'l') || truc->flag_l) ? 1 : 0;
		truc->flag_a = ((av[u] == 'a') || truc->flag_a) ? 1 : 0;
		truc->flag_t = ((av[u] == 't') || truc->flag_t) ? 1 : 0;
		truc->flag_tt = ((av[u] == 'T') || truc->flag_tt) ? 1 : 0;
		if (av[u] != '-' && av[u] != 'R' && av[u] != 'r' &&
			av[u] != 'l' && av[u] != 'a' && av[u] != 't' &&
			av[u] != 'T')
			ft_err(-1, 0);
		++u;
	}
}

int		main(int ac, char **av)
{
	t_truc	*machin;
	int		i;

	i = 0;
	if (!(machin = malloc(sizeof(t_truc))))
		ft_err(-10, 0);
	ft_initparse(machin);
	while (++i < ac)
	{
		if (av[i][0] == '-')
			parse_flag(av[i], 0, machin);
		else
			break ;
	}
	if (i == ac)
		ls_ls(machin, "./");
	while (i < ac)
	{
		ls_ls(machin, av[i]);
		if (i < ac - 1)
			write(1, "\n", 1);
		++i;
	}
}
