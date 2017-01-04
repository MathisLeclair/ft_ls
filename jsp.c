/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:38:48 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 11:48:49 by mleclair         ###   ########.fr       */
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

void	jsp_commun(t_file *lst, int i)
{
	char *str;

	str = ft_itoa(lst->size);
	if ((int)ft_strlen(str) > i)
		i = ft_strlen(str);
	free(str);
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
			jsp_commun(lst, i);
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
			jsp_commun(lst, i);
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
