/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:30 by mleclair          #+#    #+#             */
/*   Updated: 2016/12/14 19:57:24 by bfrochot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <errno.h>
# include "./libft/libft.h"

typedef struct	s_truc
{
	int flag_R;
	int flag_l;
	int flag_a;
	int flag_r;
	int flag_t;
}				t_truc;

typedef struct		s_file
{
	char			*acces;
	int				nbf;
	char			*owner;
	char			*group;
	int				size;
	char			*name;
	int				date;
	struct s_file	*prev;
	struct s_file	*next;
}					t_file;

typedef struct		r_file
{
	char			*name;
	struct r_file	*prev;
	struct r_file	*next;
}					x_file;

int		flag_R(t_truc *parse, char *path);
void	ls_core(t_truc *parse, char *av, t_file **lsd);
void	ft_lstsort(t_truc *parse, t_file *lst, int i);

#endif