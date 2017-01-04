/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:44:29 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 11:45:16 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_sortbase2(t_file *lst, int u)
{
	while (lst->prev)
	{
		if (ft_strcmp(lst->name, lst->prev->name) < 0)
		{
			if (lst->prev->prev)
				lst->prev->prev->next = lst;
			if (lst->next)
				lst->next->prev = lst->prev;
			lst->prev->next = lst->next;
			lst->next = lst->prev;
			lst->prev = lst->prev->prev;
			lst->next->prev = lst;
		}
		else
		{
			++u;
			lst = lst->prev;
		}
	}
	return (u);
}

t_file	*ft_sortbase1(t_file *lst)
{
	while (lst->next)
	{
		if (ft_strcmp(lst->name, (lst->next)->name) > 0)
		{
			if (lst->next->next)
				lst->next->next->prev = lst;
			if (lst->prev)
				lst->prev->next = lst->next;
			(lst->next)->prev = lst->prev;
			lst->prev = lst->next;
			lst->next = (lst->next)->next;
			(lst->prev)->next = lst;
		}
		else
			lst = lst->next;
	}
	return (lst);
}

int		ft_sortt2(t_file *lst, int u)
{
	while (lst->prev)
	{
		if ((lst->date > (lst->prev)->date) || ((lst->date ==
			(lst->prev)->date) && (ft_strcmp(lst->name,
			(lst->prev)->name) < 0)))
		{
			if (lst->prev->prev)
				lst->prev->prev->next = lst;
			if (lst->next)
				lst->next->prev = lst->prev;
			(lst->prev)->next = lst->next;
			lst->next = lst->prev;
			lst->prev = (lst->prev)->prev;
			(lst->next)->prev = lst;
		}
		else
		{
			++u;
			lst = lst->prev;
		}
	}
	return (u);
}

t_file	*ft_sortt1(t_file *lst)
{
	while (lst->next)
	{
		if ((lst->date < (lst->next)->date) || ((lst->date ==
		(lst->next)->date) && (ft_strcmp(lst->name, (lst->next)->name) > 0)))
		{
			if (lst->next->next)
				lst->next->next->prev = lst;
			if (lst->prev)
				lst->prev->next = lst->next;
			(lst->next)->prev = lst->prev;
			lst->prev = lst->next;
			lst->next = (lst->next)->next;
			(lst->prev)->next = lst;
		}
		else
			lst = lst->next;
	}
	return (lst);
}
