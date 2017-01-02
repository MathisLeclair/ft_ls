/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 10:59:09 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/02 19:59:30 by mleclair         ###   ########.fr       */
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
		timec = ft_strdup(timec);
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

void	ft_cpd3(t_file *lst, char **str)
{
	int		len;
	int		k;
	char	*tmp;

	tmp = ft_itoa(lst->nbf);
	k = ft_strlen(tmp);
	len = ft_strlen(*str);
	while (k > 0 && len > 0)
	{
		(*str)[len] = tmp[k];
		--len;
		--k;
	}
	free(tmp);
	lst->nbfconv = *str;
}

void	ft_cpd4(t_file *lst, char **str)
{
	int		len;
	int		k;
	char	*tmp;

	tmp = ft_itoa(lst->size);
	k = ft_strlen(tmp);
	len = ft_strlen(*str);
	while (k > 0 && len > 0)
	{
		(*str)[len] = tmp[k];
		--len;
		--k;
	}
	free(tmp);
	lst->sizeconv = *str;
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

t_file	*jsp2(t_file *lst, t_truc *parse)
{
	t_file	*sav;
	int		i;
	char	*str;

	i = 0;
	sav = lst;
	while (lst)
	{
		if (parse->flag_a == 1 || lst->name[0] != '.')
		{
			str = ft_itoa(lst->size);
			if ((int)ft_strlen(str) > i)
				i = ft_strlen(str);
			free(str);
		}
		lst = lst->next;
	}
	lst = sav;
	while (lst)
	{
		str = malloc(i + 1);
		ft_memset(str, ' ', i);
		str[i] = '\0';
		ft_cpd4(lst, &str);
		lst = lst->next;
	}
	return (sav);
}

t_file	*jsp(t_file *lst, t_truc *parse)
{
	t_file	*sav;
	int		i;
	char	*str;

	i = 0;
	sav = lst;
	while (lst)
	{
		if (parse->flag_a == 1 || lst->name[0] != '.')
		{
			str = ft_itoa(lst->nbf);
			if ((int)ft_strlen(str) > i)
				i = ft_strlen(str);
			free(str);
		}
		lst = lst->next;
	}
	lst = sav;
	while (lst)
	{
		str = malloc(i + 1);
		ft_memset(str, ' ', i);
		str[i] = '\0';
		ft_cpd3(lst, &str);
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
	tmp = malloc(ft_strlen(lst->path) + ft_strlen(lst->name) + 1);
	*tmp = 0;
	ft_strcat(tmp, lst->path);
	ft_strcat(tmp, lst->name);
	len = readlink(tmp, str, 9999);
	free(tmp);
	new = malloc(len + 5 + ft_strlen(lst->name));
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

void	print_c(t_file *lst, t_truc *parse)
{
	char *time;

	time = conv_time(lst->date, parse);
	while ((lst->major / 256) > 0)
		lst->major = lst->major / 256;
	ft_printf("%s %s %s  %s  %2d, %3d%s %s%s%s\n", lst->acces,
		lst->nbfconv, lst->owner,
		lst->group, lst->major, lst->minor, time, ft_color(lst, 1),
		lst->name, ft_color(lst, 0));
	free(time);
}

void	print_l_too_long(t_truc *parse, t_file *lst)
{
	char *time;

	if ((lst->name[0] != '.' || parse->flag_a == 1) && lst->type != 'c')
	{
		if (lst->type == 'l')
			linkatt(lst);
		time = conv_time(lst->date, parse);
		ft_printf("%s %s %s  %s  %s%s %s%s%s\n", lst->acces,
			lst->nbfconv, lst->owner,
			lst->group, lst->sizeconv, time, ft_color(lst, 1),
			lst->name, ft_color(lst, 0));
		free(time);
	}
	else if (lst->type == 'c')
		print_c(lst, parse);
}

void	print_l(t_file *lst, t_truc *parse)
{
	if (lst->group)
	{
		lst = group_l(lst);
		lst = owner_l(lst);
		lst = jsp(lst, parse);
		lst = jsp2(lst, parse);
		ft_prtot(lst, parse);
	}
	while (lst->next)
	{
		if (lst->owner == NULL && !parse->flag_r &&
			(lst->name[0] != '.' || parse->flag_a == 1))
			ft_printf("ft_ls: %s: T'avais pas l'droit !\n", lst->name);
		else if (lst->owner && !parse->flag_r)
			print_l_too_long(parse, lst);
		lst = lst->next;
	}
	if (lst->owner == NULL && !parse->flag_r &&
		(lst->name[0] != '.' || parse->flag_a == 1))
		ft_printf("ft_ls: %s: T'avais pas l'droit !\n", lst->name);
	else if (lst->owner && !parse->flag_r)
		print_l_too_long(parse, lst);
	while (parse->flag_r && lst)
	{
		if (lst->owner == NULL && (lst->name[0] != '.' || parse->flag_a == 1))
			ft_printf("ft_ls: %s: T'avais pas l'droit !\n", lst->name);
		else
			print_l_too_long(parse, lst);
		lst = lst->prev;
	}
}
