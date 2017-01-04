/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 10:59:09 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 18:01:10 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*conv_time(long int date, t_truc *parse)
{
	char		*timec;
	int			i;
	int			len;
	long int	rtime;

	i = -1;
	timec = ctime(&date);
	rtime = time(NULL);
	len = ft_strlen(timec);
	while (++i < 3)
		timec++;
	if (parse->flag_tt == 0 && (date < (rtime - (2592000 * 6))))
		timec = timef2(timec);
	else
	{
		timec = ft_strdup(timec);
		i = (parse->flag_tt == 0) ? 13 : 10;
		while (i--)
			timec[len - i] = '\0';
	}
	return (timec);
}

t_file	*group_l(t_file *lst)
{
	t_file	*sav;
	int		i;
	char	*str;

	i = 0;
	sav = lst;
	while (lst)
	{
		if ((int)ft_strlen(lst->group) > i)
			i = ft_strlen(lst->group);
		lst = lst->next;
	}
	lst = sav;
	while (lst)
	{
		if (!(str = malloc(i + 1)))
			ft_err(-10, 0);
		ft_memset(str, ' ', i);
		str[i] = '\0';
		ft_cpd2(lst, str);
		lst = lst->next;
	}
	lst = sav;
	return (lst);
}

t_file	*owner_l(t_file *lst)
{
	t_file	*sav;
	int		i;
	char	*str;

	i = 0;
	sav = lst;
	while (lst)
	{
		if ((int)ft_strlen(lst->owner) > i)
			i = ft_strlen(lst->owner);
		lst = lst->next;
	}
	lst = sav;
	while (lst)
	{
		if (!(str = malloc(i + 1)))
			ft_err(-10, 0);
		ft_memset(str, ' ', i);
		str[i] = '\0';
		ft_cpd(lst, str);
		lst = lst->next;
	}
	return (sav);
}

void	linkatt(t_file *lst)
{
	char	str[10000];
	int		len;
	char	*new;
	char	*tmp;

	ft_bzero(str, 10000);
	if (!(tmp = malloc(ft_strlen(lst->path) + ft_strlen(lst->name) + 1)))
		ft_err(-10, 0);
	*tmp = 0;
	ft_strcat(tmp, lst->path);
	ft_strcat(tmp, lst->name);
	len = readlink(tmp, str, 9999);
	free(tmp);
	if (!(new = malloc(len + 5 + ft_strlen(lst->name))))
		ft_err(-10, 0);
	*new = 0;
	ft_strcat(new, lst->name);
	ft_strcat(new, " -> ");
	ft_strcat(new, str);
	tmp = lst->name;
	lst->name = new;
	free(tmp);
}

void	ft_prtot(t_file *lst, t_truc *parse)
{
	int i;

	i = 0;
	while (lst)
	{
		if (lst->name[0] != '.' || parse->flag_a == 1)
			i += lst->total;
		lst = lst->next;
	}
	ft_printf("total %d\n", i);
}
