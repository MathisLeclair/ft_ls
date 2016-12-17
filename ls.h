/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:30 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/17 17:41:32 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <pwd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <errno.h>
# include <grp.h>
# include "./libft/libft.h"

typedef struct	s_truc
{
	int flag_R;
	int flag_l;
	int flag_a;
	int flag_r;
	int flag_t;
	int	flag_T;
}				t_truc;

typedef struct		s_file
{
	char			*acces;
	char			type;
	int				nbf;
	char			*owner;
	char			*group;
	int				size;
	char			*name;
	long int		date;
	struct s_file	*prev;
	struct s_file	*next;
}					x_file;

typedef struct		r_file
{
	char			*name;
	struct r_file	*prev;
	struct r_file	*next;
}					u_file;

int		flag_R(t_truc *parse, char *path);
void	ls_core(t_truc *parse, char *av, x_file **lsd);
void	ft_lstsort(t_truc *parse, x_file *lst, int i);
void	print_l(x_file *lst, t_truc *parse);

#endif