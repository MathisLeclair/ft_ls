/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:17 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/14 18:25:07 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_err(int i)
{
	if (i == -1)
	{
		ft_printf("Illegal flag.\nusage: ./ls [-rRatl]\n");
		exit(-1);
	}
}

void	ls_ls(t_truc *machin, char *av)
{
	t_file *lsd;

	if (machin->flag_R == 1)
		flag_R(machin, av);
	else
		ls_core(machin, av, &lsd);
}

void	parse_flag(char *av, int u, t_truc *machin)
{
	while(av[u])
	{
		if (av[u] == 'R')
			machin->flag_R = 1;
		else if(av[u] == 'r')
			machin->flag_r = 1;
		else if(av[u] == 'l')
			machin->flag_l = 1;
		else if(av[u] == 'a')
			machin->flag_a = 1;
		else if(av[u] == 't')
			machin->flag_t = 1;
		else if(av[u] != '-' && av[u] != 'R' && av[u] != 'r' &&
			av[u] != 'l' && av[u] != 'a' && av[u] != 't')
			ft_err(-1);
		++u;
	}
}

int		main(int ac, char **av)
{
	t_truc *machin;
	int k;

	machin = malloc(sizeof(t_truc));
	k = 1;
	if (ac > 1)
		k = (av[1][0] == '-' ? 2 : 1);
	if (k == 2)
		parse_flag(av[1], 0, machin);
	if (ac == 0 || (ac == 2 && k == 2) || (ac == 1 && k == 1))
		ls_ls(machin, "./");
	while (k < ac)
	{
		ls_ls(machin, av[k]);
		if (k < ac - 1)
			write(1, "\n", 1);
		++k;
	}
}
