/* *************************************************************	************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:58:32 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 14:57:39 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_lstcreate(struct dirent *dp, t_file *lst, DIR *dir, char *path)
{
	int i;

	i = 1;
	while ((dp = readdir(dir)))
	{
		lst->next = ft_elemcreate(dp, path);
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
		*lsd = ft_elemcreate(dp, path);
		ft_lstsort(parse, *lsd, ft_lstcreate(dp, *lsd, dir, path));
		while ((*lsd)->prev)
			(*lsd) = (*lsd)->prev;
		if (parse->flag_l == 0)
			ls_core_to_long(parse, lsd);
		else
			print_l((*lsd), parse);
	}
	while ((*lsd)->prev && !parse->flag_r && parse->flag_rr)
		*lsd = (*lsd)->prev;
	closedir(dir);
	free(path);
}
