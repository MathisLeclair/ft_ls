/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 21:38:09 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/07 11:39:48 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt_parts(const char *s, char c)
{
	int i;
	int nw;

	i = 0;
	nw = 0;
	while (s[i++])
		if ((s[i - 1] == c || nw == 0) && s[i] != c && s[i] != '\0')
			nw++;
	return (nw);
}

static int	ft_wlen(const char *s, char c)
{
	int		l;

	l = 0;
	while (*s != c && *s != '\0')
	{
		l++;
		s++;
	}
	return (l);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**a;
	int		nbw;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	nbw = ft_cnt_parts((const char *)s, c);
	a = (char **)malloc(sizeof(*a) * (ft_cnt_parts((const char *)s, c) + 1));
	if (a == NULL)
		return (NULL);
	while (nbw--)
	{
		while (*s == c && *s != '\0')
			s++;
		a[i] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
		if (a[i] == NULL)
			return (NULL);
		s = s + ft_wlen(s, c);
		i++;
	}
	a[i] = NULL;
	return (a);
}
