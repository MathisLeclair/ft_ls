/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:17 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/18 17:30:34 by mleclair         ###   ########.fr       */
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
	t_file *lsd;

	if (machin->flag_rr == 1)
		flag_r(machin, av);
	else
		ls_core(machin, av, &lsd);
}

t_truc	*ft_initparse(t_truc *machin)
{
	machin->flag_rr = 0;
	machin->flag_r = 0;
	machin->flag_t = 0;
	machin->flag_tt = 0;
	machin->flag_a = 0;
	machin->flag_l = 0;
	return (machin);
}

t_truc	*parse_flag(char *av, int u, int k)
{
	t_truc *truc;

	truc = malloc(sizeof(t_truc));
	truc = ft_initparse(truc);
	while (av[u])
	{
		truc->flag_rr = ((k == 2 && av[u] == 'R') || truc->flag_rr) ? 1 : 0;
		truc->flag_r = ((k == 2 && av[u] == 'r') || truc->flag_r) ? 1 : 0;
		truc->flag_l = ((k == 2 && av[u] == 'l') || truc->flag_l) ? 1 : 0;
		truc->flag_a = ((k == 2 && av[u] == 'a') || truc->flag_a) ? 1 : 0;
		truc->flag_t = ((k == 2 && av[u] == 't') || truc->flag_t) ? 1 : 0;
		truc->flag_tt = ((k == 2 && av[u] == 'T') || truc->flag_tt) ? 1 : 0;
		if (av[u] != '-' && av[u] != 'R' && av[u] != 'r' &&
			av[u] != 'l' && av[u] != 'a' && av[u] != 't' &&
			av[u] != 'T' && k == 2)
			ft_err(-1);
		++u;
	}
	return (truc);
}

int		main(int ac, char **av)
{
	t_truc	*machin;
	int		k;

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
