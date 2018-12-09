/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:25:18 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 15:25:19 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		create_new_dec_nodes(t_s *ls, t_pa *path, t_d *d)
{
	int		count;
	t_d		*tmp_d;

	count = 0;
	tmp_d = d;
	while (path)
	{
		if (!cross_test(ls, d, path))
		{
			if (count)
			{
				while (tmp_d->next)
					tmp_d = tmp_d->next;
				tmp_d->next = dec_cpy(ls, d, 1);
				tmp_d = tmp_d->next;
			}
			count++;
		}
		path = path->next;
	}
}

static void		search_w_o_crosses(t_s *ls, t_d *d, int index, int direct)
{
	t_pa	*path;
	t_d		*dec_to_cmp;
	t_d		*tmp_d;

	d->decision[d->decision_size++] = index;
	d->direct = (d->direct == 1 ? 1 : direct);
	dec_to_cmp = dec_cpy(ls, d, 0);
	create_new_dec_nodes(ls, ls->p, d);
	path = ls->p;
	tmp_d = d;
	while (path)
	{
		if (tmp_d && !cross_test(ls, tmp_d, path))
		{
			search_w_o_crosses(ls, tmp_d, path->index,
				path->path_size == 2 ? 1 : 0);
			while (tmp_d && dec_cmp(dec_to_cmp, tmp_d))
				tmp_d = tmp_d->next;
		}
		path = path->next;
	}
	free(dec_to_cmp->decision);
	free(dec_to_cmp);
}

static void		find_decisions2(t_s *ls, t_d *d, t_pa *path)
{
	while (path)
	{
		search_w_o_crosses(ls, d, path->index,
			path->path_size == 2 ? 1 : 0);
		if (path->next)
		{
			while (d->next)
				d = d->next;
			if (!(d->next = (t_d*)malloc(sizeof(t_d))))
				error(ls, 1);
			if (!(d->next->decision = (int*)malloc(sizeof(int) *
				ls->max_paths)))
				error(ls, 1);
			d = d->next;
			d->index = ls->dec_found++;
			d->decision_size = 0;
			d->direct = 0;
			d->next = NULL;
		}
		path = path->next;
	}
}

void			find_decisions(t_s *ls)
{
	if (!(ls->d = (t_d*)malloc(sizeof(t_d))))
		error(ls, 1);
	if (!(ls->d->decision = (int*)malloc(sizeof(int) * ls->max_paths)))
		error(ls, 1);
	ls->d->index = ls->dec_found++;
	ls->d->decision_size = 0;
	ls->d->direct = 0;
	ls->d->next = NULL;
	find_decisions2(ls, ls->d, ls->p);
}
