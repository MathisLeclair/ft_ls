/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:17 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/17 18:11:40 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_err(int i)
{
	if (i == -1)
	{
		ft_printf("Illegal flag.\nusage: ./ls [-rRatTl]\n");
		exit(-1);
	}
}

void	ls_ls(t_truc *machin, char *av)
{
	x_file *lsd;

	if (machin->flag_R == 1)
		flag_R(machin, av);
	else
		ls_core(machin, av, &lsd);
}

t_truc	*ft_initparse(t_truc *machin)
{
	machin->flag_R = 0;
	machin->flag_r = 0;
	machin->flag_t = 0;
	machin->flag_T = 0;
	machin->flag_a = 0;
	machin->flag_l = 0;
	return (machin);
}

t_truc	*parse_flag(char *av, int u, int k)
{
	t_truc *machin;

	machin = malloc(sizeof(t_truc));
	machin = ft_initparse(machin);
	while(av[u])
	{
		machin->flag_R = ((k == 2 && av[u] == 'R') || machin->flag_R) ? 1 : 0;
		machin->flag_r = ((k == 2 && av[u] == 'r') || machin->flag_r) ? 1 : 0;
		machin->flag_l = ((k == 2 && av[u] == 'l') || machin->flag_l) ? 1 : 0;
		machin->flag_a = ((k == 2 && av[u] == 'a') || machin->flag_a) ? 1 : 0;
		machin->flag_t = ((k == 2 && av[u] == 't') || machin->flag_t) ? 1 : 0;
		machin->flag_T = ((k == 2 && av[u] == 'T') || machin->flag_T) ? 1 : 0;
		if(av[u] != '-' && av[u] != 'R' && av[u] != 'r' &&
			av[u] != 'l' && av[u] != 'a' && av[u] != 't' &&
			av[u] != 'T' && k == 2)
			ft_err(-1);
		++u;
	}
	return (machin);
}

int		main(int ac, char **av)
{
	t_truc *machin;
	int k;

	k = 1;
	if (ac > 1)
	{
		k = (av[1][0] == '-' ? 2 : 1);
		machin = parse_flag(av[1], 0, k);
	}
	else
		machin = parse_flag(" ", 0, k);
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
