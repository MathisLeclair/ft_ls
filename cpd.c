/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:34:35 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 18:56:58 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_cpd(t_file *lst, char *str)
{
	int len;

	len = 0;
	while (lst->owner && lst->owner[len])
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
	while (lst->group && lst->group[len])
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
	while (k >= 0 && len >= 0)
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
	while (k >= 0 && len >= 0)
	{
		(*str)[len] = tmp[k];
		--len;
		--k;
	}
	free(tmp);
	lst->sizeconv = *str;
}
