/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:12:51 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/14 18:24:18 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		flag_R(t_truc *parse, char *path)
{
	// DIR *dir;
	// DIR *dir2;
	char *caca;
	// struct dirent *dp;
	t_file *lsd;

	caca = malloc(2000);
	caca[0] = 0;
	ls_core(parse, path, &lsd);
	// while ((dp = readdir(dir)))
	// {
		// if ((dp->d_name[0] != '.' || dp->d_name[1] != 0) && (dp->d_name[1] != '.' || dp->d_name[2] != 0))
		// {
		// 	caca = ft_strcat(caca, path);
		// 	if (caca[ft_strlen(caca) - 1] != '/')
		// 		ft_strcat(caca, "/");
		// 	caca = ft_strcat(caca, dp->d_name);
		// 	if ((dir2 = opendir(caca)))
		// 	{
		// 		closedir(dir2);
		// 		write(1, "\n", 1);
		// 		ft_printf("%s\n", caca);
		// 		caca = ft_strcat(caca, "/");
		// 		flag_R(parse, caca);
		// 	}
		// 	else if (errno == 13)
		// 		ft_printf("\n%s:\nft_ls: %s: Permission denied\n", caca, dp->d_name);
		// 	caca[0] = 0;
		// }
	// }
	free(lsd);
	return (0);
}
