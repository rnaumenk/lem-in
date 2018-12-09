/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:09:13 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/07 19:12:21 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# include "../libft/include/libft.h"

typedef struct		s_m
{
	char			**path;
	int				*ant_index;
	int				path_size;
	int				direct;
}					t_m;

typedef struct		s_d
{
	int				index;
	int				*decision;
	int				decision_size;
	int				direct;
	struct s_d		*next;
}					t_d;

typedef struct		s_pa
{
	int				index;
	int				*path;
	int				path_size;
	struct s_pa		*next;
}					t_pa;

typedef struct		s_r
{
	char			*name;
	int				x;
	int				y;
	int				start;
	int				end;
	int				index;
	int				*link;
	int				link_size;
	struct s_r		*next;
}					t_r;

typedef struct		s_s
{
	int				arg1;
	int				arg2;
	int				arg3;
	int				arg4;
	int				input_lines;
	char			*line;
	char			*input;
	int				start;
	int				end;
	int				ant_number;
	int				ant_num_found;
	t_r				*r;
	t_pa			*p;
	t_d				*d;
	t_d				*best_dec;
	t_m				**m;
	int				best_dec_size;
	int				best_steps;
	int				room_quantity;
	int				link_found;
	int				max_paths;
	int				path_found;
	int				end_index;
	int				dec_found;
	int				max_path_size;
	long			min_ant_index;
	int				steps;
	int				best_paths;
	int				fullfilled;
}					t_s;

void				trial(t_s *ls, t_m *m, long k, int l);
int					calculate_the_best_output(t_s *ls, int b);
t_pa				*path_cpy(t_s *ls, t_pa *path, int k);
t_d					*dec_cpy(t_s *ls, t_d *d, int k);
int					path_cmp(t_pa *p1, t_pa *p2);
int					dec_cmp(t_d *d1, t_d *d2);
void				create_the_link(t_s *ls);
void				create_the_room(t_s *ls);
void				find_decisions(t_s *ls);
void				error(t_s *ls, int n);
void				free_split(char ***temp);
void				choose_the_color(t_s *ls, int a, char *s);
void				try_to_finish(t_s *ls);
void				move_this_shit(t_s *ls);
void				find_the_path(t_s *ls, t_pa *path, t_r *start, int i);
void				find_all_possible(t_s *ls, int i);
void				go(t_s *ls, t_m *m, long k, int l);
void				solve_this_shit(t_s *ls);
void				sort_int_tab(int *tab, int size);
void				sort(t_m *m, t_d *d);
void				sort_dec(t_d *d);
void				new_path_initialization(t_s *ls, t_pa *path, t_r *start);
int					cross_test(t_s *ls, t_d *d, t_pa *path);
int					empty(t_m *m, int l);
void				validation(t_s *ls);

#endif
