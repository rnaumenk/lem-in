/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:26:46 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:26:49 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		create_the_data(t_s *ls, t_pa *path, int i, int k)
{
	t_r		*r;
	int		j;

	if (!(ls->m[k][i].path = (char**)malloc(sizeof(char*) *
		(path->path_size - 1))))
		error(ls, 1);
	r = ls->r;
	while (r)
	{
		j = 0;
		while (++j < path->path_size)
		{
			if (r->index == path->path[j])
				ls->m[k][i].path[j - 1] = r->name;
		}
		r = r->next;
	}
	if (!(ls->m[k][i].ant_index = (int*)malloc(sizeof(int) *
		(path->path_size - 1))))
		error(ls, 1);
	j = -1;
	while (++j < path->path_size - 1)
		ls->m[k][i].ant_index[j] = 0;
	ls->m[k][i].path_size = path->path_size - 1;
	ls->m[k][i].direct = (path->path_size == 2 ? 1 : 0);
}

static void		paths_output(t_s *ls, t_pa *pp, t_r *r, int j)
{
	(ls->arg3 ? ft_printf("%sPaths found:%s\n", KGRN, KNRM) :
		ft_printf("Paths found:\n"));
	while (pp)
	{
		(ls->arg3 ? ft_printf("%s%d: %s", KYEL, pp->index, KCYN) :
			ft_printf("%d: ", pp->index));
		j = 0;
		while (++j < pp->path_size)
		{
			r = ls->r;
			while (r)
			{
				if (r->index == pp->path[j])
					ft_printf("->%s", r->name);
				r = r->next;
			}
		}
		ft_printf("\n");
		pp = pp->next;
	}
	(ls->arg3 ? ft_printf("%s_________________________\n", KMAG) :
		ft_printf("_________________________\n"));
}

static void		decs_output(t_s *ls, t_d *dd, int k, int i)
{
	int		j;
	int		g;

	(ls->arg3 ? ft_printf("%sDecisions found:%s\n", KGRN, KNRM) :
		ft_printf("Decisions found:\n"));
	while (++i < ls->dec_found)
	{
		(ls->arg3 ? ft_printf("%s#%d:%s\n", KYEL, i + 1, KCYN) :
			ft_printf("#%d:\n", i + 1));
		j = -1;
		while (++j < dd->decision_size)
		{
			g = -1;
			while (++g < ls->m[i][j].path_size)
				ft_printf("->%s", ls->m[i][j].path[g]);
			ft_printf("\n");
		}
		dd = dd->next;
	}
	(ls->arg3 ?
		ft_printf("%s\nDecision chosen - #%d\n", KGRN, ls->best_paths + 1) :
		ft_printf("\nDecision chosen - #%d\n", ls->best_paths + 1));
	(ls->arg3 ?
		ft_printf("Paths taken - %d%s\n_________________________\n", k, KMAG) :
		ft_printf("Paths taken - %d\n_________________________\n", k));
}

static void		malloc_this_shit(t_s *ls, int k)
{
	t_d		*d;
	t_pa	*p;
	int		i;
	int		j;

	d = ls->d;
	while (++k < ls->dec_found)
	{
		if (!(ls->m[k] = (t_m*)malloc(sizeof(t_m) * d->decision_size)))
			error(ls, 1);
		i = 0;
		p = ls->p;
		while (p)
		{
			j = -1;
			while (++j < d->decision_size)
			{
				if (p->index == d->decision[j])
					create_the_data(ls, p, i++, k);
			}
			p = p->next;
		}
		d = d->next;
	}
}

void			move_this_shit(t_s *ls)
{
	t_d		*d;
	int		k;

	if (!(ls->m = (t_m**)malloc(sizeof(t_m*) * ls->dec_found)))
		error(ls, 1);
	malloc_this_shit(ls, -1);
	d = ls->d;
	k = -1;
	while (++k < ls->dec_found)
	{
		sort(ls->m[k], d);
		d = d->next;
	}
	k = calculate_the_best_output(ls, 2147483647);
	if (ls->arg1)
		paths_output(ls, ls->p, ls->r, 0);
	if (ls->arg2)
		decs_output(ls, ls->d, k, -1);
	go(ls, ls->m[ls->best_paths], 1, k);
}
