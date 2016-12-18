/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 10:59:09 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/18 19:11:39 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*timef2(char *timec)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(14);
	tmp[0] = ' ';
	tmp[1] = timec[1];
	tmp[2] = timec[2];
	tmp[3] = timec[3];
	tmp[4] = ' ';
	tmp[5] = timec[8];
	tmp[6] = timec[9];
	tmp[7] = ' ';
	tmp[8] = ' ';
	tmp[9] = timec[17];
	tmp[10] = timec[18];
	tmp[11] = timec[19];
	tmp[12] = timec[20];
	tmp[13] = '\0';
	return (tmp);
}

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
		i = (parse->flag_tt == 0) ? 13 : 10;
		while (i--)
			timec[len - i] = '\0';
	}
	return (timec);
}

void	ft_cpd(t_file *lst, char *str)
{
	int len;

	len = 0;
	while (lst->owner[len])
	{
		str[len] = lst->owner[len];
		len++;
	}
	free(lst->owner);
	lst->owner = str;
}

void	ft_cpd2(t_file *lst, char *str)
{
	int len;

	len = 0;
	while (lst->group[len])
	{
		str[len] = lst->group[len];
		len++;
	}
	free(lst->group);
	lst->group = str;
}

t_file	*group_l(t_file *lst)
{
	t_file	*sav;
	int		i;
	char	*str;

	i = 0;
	sav = malloc(sizeof(t_file));
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
		str = malloc(i + 1);
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
		str = malloc(i + 1);
		ft_memset(str, ' ', i);
		str[i] = '\0';
		ft_cpd(lst, str);
		lst = lst->next;
	}
	return (sav);
}

void	print_l(t_file *lst, t_truc *parse)
{
	char *time;

	lst = group_l(lst);
	lst = owner_l(lst);
	while (lst)
	{
		if (lst->name[0] != '.' || parse->flag_a == 1)
		{
			time = conv_time(lst->date, parse);
			ft_printf("%s%5d %s %s %5d %s %s\n", lst->acces, lst->nbf, lst->owner,
				lst->group, lst->size, time, lst->name);
		}
		lst = lst->next;
	}
}
