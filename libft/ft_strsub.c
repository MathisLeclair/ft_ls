/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:41:08 by mleclair          #+#    #+#             */
/*   Updated: 2016/11/08 09:41:15 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	return (str);
}
