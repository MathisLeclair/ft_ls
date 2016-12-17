/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 19:57:55 by bfrochot          #+#    #+#             */
/*   Updated: 2016/12/17 16:48:05 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_sortbase2(x_file *lst, int u)
{
	while (lst->prev)
	{
		if(ft_strcmp(lst->name, (lst->prev)->name) < 0)
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

x_file	*ft_sortbase1(x_file *lst)
{
	while (lst->next)
	{
		if(ft_strcmp(lst->name, (lst->next)->name) > 0)
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

int		ft_sortr2(x_file *lst, int u)
{
	while (lst->prev)
	{
		if((lst->date < (lst->prev)->date) || ((lst->date == (lst->prev)->date) && (ft_strcmp(lst->name, (lst->prev)->name) < 0)))
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

x_file	*ft_sortr1(x_file *lst)
{
	while (lst->next)
	{
		if((lst->date > (lst->next)->date) || ((lst->date == (lst->next)->date) && (ft_strcmp(lst->name, (lst->next)->name) > 0)))
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

int		ft_sortt2(x_file *lst, int u)
{
	while (lst->prev)
	{
		if((lst->date > (lst->prev)->date) || ((lst->date == (lst->prev)->date) && (ft_strcmp(lst->name, (lst->prev)->name) < 0)))
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

x_file	*ft_sortt1(x_file *lst)
{
	while (lst->next)
	{
		if((lst->date < (lst->next)->date) || ((lst->date == (lst->next)->date) && (ft_strcmp(lst->name, (lst->next)->name) > 0)))
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

void	ft_lstsort(t_truc *parse, x_file *lst, int i)
{
	int u;

	u = 0;
	if (parse->flag_t == 0 && parse->flag_r == 0)
		while (u != (i - 1))
		{
			lst = ft_sortbase1(lst);
			u = ft_sortbase2(lst, 0);
		}
	if(parse->flag_r == 1)
		while (u != (i - 1))
		{
			lst = ft_sortr1(lst);
			u = ft_sortr2(lst, 0);
		}
	else if (parse->flag_t ==1 && parse->flag_r == 0)
		while (u != (i - 1))
		{
			lst = ft_sortt1(lst);
			u = ft_sortt2(lst, 0);
		}
}
