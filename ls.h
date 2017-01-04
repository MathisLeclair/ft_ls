/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:20:30 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/04 17:49:22 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <unistd.h>
# include <dirent.h>
# include <uuid/uuid.h>
# include <stdlib.h>
# include <time.h>
# include <pwd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <errno.h>
# include <grp.h>
# include "./libft/libft.h"

typedef struct		s_truc
{
	int				flag_rr;
	int				flag_l;
	int				flag_a;
	int				flag_r;
	int				flag_t;
	int				flag_tt;
}					t_truc;

typedef struct		s_file
{
	char			*acces;
	char			type;
	int				nbf;
	char			*nbfconv;
	char			*owner;
	int				total;
	char			*group;
	int				size;
	char			*sizeconv;
	char			*name;
	long int		date;
	char			*path;
	int				major;
	int				minor;
	struct s_file	*prev;
	struct s_file	*next;
}					t_file;

void				list_free_inner(t_file *lst);
void				flag_rr(t_truc *parse, char *path);
void				ls_core(t_truc *parse, char *av, t_file **lsd);
void				ft_lstsort(t_truc *parse, t_file *lst, int i);
void				print_l(t_file *lst, t_truc *parse);
char				*ft_strrev(char *str);
int					ft_err(int i, char *tmp);
void				list_free(t_file *lst);
char				*ft_color(t_file *lsd, int i);

void				ft_cpd(t_file *lst, char *str);
void				ft_cpd2(t_file *lst, char *str);
void				ft_cpd3(t_file *lst, char **str);
void				ft_cpd4(t_file *lst, char **str);

void				ft_elemcreate2(t_file *lsd, struct stat *buf, char *path, char *pathnm);
void				lst_l_prepare(t_file *lst, t_truc *parse, int boi);

void				ft_prtot(t_file *lst, t_truc *parse);
void				linkatt(t_file *lst);
t_file				*owner_l(t_file *lst);
t_file				*group_l(t_file *lst);
char				*conv_time(long int date, t_truc *parse);
char				*timef2(char *timec);

t_file				*jsp(t_file *lst, t_truc *parse);
t_file				*jsp2(t_file *lst, t_truc *parse);
int					jsp_commun(t_file *lst, int i);
char				*timef2(char *timec);

t_file				*ft_sortt1(t_file *lst);
int					ft_sortt2(t_file *lst, int u);
t_file				*ft_sortbase1(t_file *lst);
int					ft_sortbase2(t_file *lst, int u);

char				*ft_pathname(char *path, char *name);
t_file				*ft_elemcreate(struct dirent *dp, char *path);
void				lsd_null(t_file *lsd);
char				*ft_color(t_file *lsd, int i);
char				type(struct stat *buf);
char				*droit(int mode, t_file *lsd, char *path);

#endif
