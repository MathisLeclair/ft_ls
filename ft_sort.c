/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:04:14 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 11:45:03 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_listlen(t_file *lst)
{
	int i;

	i = 0;
	while (lst->next)
	{
		++i;
		lst = lst->next;
	}
	++i;
	while (lst->prev)
		lst = lst->prev;
	return (i);
}

void	ft_revlist(t_file *lst)
{
	t_file	*tmp;
	int		i;

	while (lst->prev)
		lst = lst->prev;
	i = ft_listlen(lst);
	while (lst->next)
		lst = lst->next;
	while (i > 0)
	{
		tmp = lst->next;
		lst->next = lst->prev;
		lst->prev = tmp;
		lst = lst->next;
		--i;
	}
}

void	ft_lstsort(t_truc *parse, t_file *lst, int i)
{
	int u;

	u = 0;
	if (parse->flag_t == 0)
		while (u != (i - 1))
		{
			lst = ft_sortbase1(lst);
			u = ft_sortbase2(lst, 0);
		}
	if (parse->flag_t == 1)
		while (u != (i - 1))
		{
			lst = ft_sortt1(lst);
			u = ft_sortt2(lst, 0);
		}
	if (parse->flag_r == 1)
		ft_revlist(lst);
}
