/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 14:23:31 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/14 18:24:57 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <fcntl.h>

int main()
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(".");
	dp = readdir(dir);
	free(dp->d_name);
//	free(dp);
}