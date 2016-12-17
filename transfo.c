/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 10:59:09 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/17 18:12:54 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*conv_time(long int date, t_truc *parse)
{
	char *time;
	int i;
	int len;

	i = -1;
	time = ctime(&date);
	len = ft_strlen(time);
	while (++i < 3)
		time++;
	i = 13;
	if (parse->flag_T == 0)
		while (i--)
			time[len - i] = '\0';
	else
	{
		i = 10;
		while (i--)
			time[len - i] = '\0';
	}
	// time[ft_strlen(time) - 1] = '\0';
	return(time);
}

void	print_l(x_file *lst, t_truc *parse)
{
	char *time;

	while(lst)
	{
		if (lst->name[0] != '.'|| parse->flag_a == 1)
		{
			time = conv_time(lst->date, parse);
			ft_printf("%s%5d %s %s %6d %s %s\n", lst->acces, lst->nbf, lst->owner, lst->group, lst->size, time,lst->name);
		}
		lst = lst->next;
	}
}