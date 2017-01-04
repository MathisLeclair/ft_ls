/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:17 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 14:52:39 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_err(int i, char *tmp)
{
	if (i == -1)
	{
		ft_printf("Illegal flag.\nusage: ./ls [-rRatTl]\n");
		exit(-1);
	}
	else if (i == -10)
	{
		ft_printf("Allocation error. Bitch.\n");
		exit(-2);
	}
	else if (errno == ENOTDIR)
		ft_printf("%s\n", tmp);
	else
	{
		ft_printf("ft_ls: %s: ", tmp);
		perror(NULL);
		exit(0);
	}
	return (1);
}

void	ls_ls(t_truc *machin, char *av)
{
	t_file *lsd;

	if (machin->flag_rr == 1)
		flag_rr(machin, av);
	else
	{
		ls_core(machin, av, &lsd);
		list_free(lsd);
	}
}

void	ft_initparse(t_truc *machin)
{
	machin->flag_rr = 0;
	machin->flag_r = 0;
	machin->flag_t = 0;
	machin->flag_tt = 0;
	machin->flag_a = 0;
	machin->flag_l = 0;
}

void	parse_flag(char *av, int u, t_truc *truc)
{
	while (av[u])
	{
		truc->flag_rr = ((av[u] == 'R') || truc->flag_rr) ? 1 : 0;
		truc->flag_r = ((av[u] == 'r') || truc->flag_r) ? 1 : 0;
		truc->flag_l = ((av[u] == 'l') || truc->flag_l) ? 1 : 0;
		truc->flag_a = ((av[u] == 'a') || truc->flag_a) ? 1 : 0;
		truc->flag_t = ((av[u] == 't') || truc->flag_t) ? 1 : 0;
		truc->flag_tt = ((av[u] == 'T') || truc->flag_tt) ? 1 : 0;
		if (av[u] != '-' && av[u] != 'R' && av[u] != 'r' &&
			av[u] != 'l' && av[u] != 'a' && av[u] != 't' &&
			av[u] != 'T')
			ft_err(-1, 0);
		++u;
	}
}

int		main(int ac, char **av)
{
	t_truc	*machin;
	int		i;

	i = 0;
	if (!(machin = malloc(sizeof(t_truc))))
		ft_err(-10, 0);
	ft_initparse(machin);
	while (++i < ac)
	{
		if (av[i][0] == '-')
			parse_flag(av[i], 0, machin);
		else
			break ;
	}
	if (i == ac)
		ls_ls(machin, "./");
	while (i < ac)
	{
		ls_ls(machin, av[i]);
		if (i < ac - 1)
			write(1, "\n", 1);
		++i;
	}
}
