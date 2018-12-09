/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:27:05 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:27:08 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		new_indexes(t_s *ls, t_pa *path)
{
	int		i;

	i = 0;
	while (path)
	{
		if (ls->max_path_size < path->path_size)
			ls->max_path_size = path->path_size;
		path->index = i++;
		path = path->next;
	}
}

static void		del_wasted(t_s *ls, t_pa *path, t_pa *prev, t_pa *next)
{
	while (path)
	{
		next = path->next;
		if (path->path[path->path_size - 1] != ls->end_index)
		{
			ls->path_found--;
			free(path->path);
			free(path);
			path = NULL;
			if (prev)
			{
				prev->next = next;
				path = prev;
			}
			else
				ls->p = next;
		}
		prev = path;
		path = next;
	}
}

static void		del_repeating_decisions(t_s *ls, t_d *d, t_d *prev, t_d *next)
{
	sort_dec(d);
	while (d->next)
	{
		prev = d;
		next = d->next;
		while (next)
		{
			if (!dec_cmp(d, next))
			{
				prev->next = next->next;
				ls->dec_found--;
				free(next->decision);
				free(next);
				next = prev->next;
			}
			else
			{
				prev = prev->next;
				next = next->next;
			}
		}
		if (d->next)
			d = d->next;
	}
}

void			solve_this_shit(t_s *ls)
{
	t_r		*start;
	t_r		*end;

	start = ls->r;
	end = ls->r;
	while (start && start->start != 1)
		start = start->next;
	while (end && end->end != 1)
		end = end->next;
	ls->max_paths = (start->link_size <= end->link_size ? start->link_size :
		end->link_size);
	find_all_possible(ls, -1);
	del_wasted(ls, ls->p, NULL, ls->p->next);
	if (!ls->p)
		error(ls, 19);
	new_indexes(ls, ls->p);
	find_decisions(ls);
	del_repeating_decisions(ls, ls->d, ls->d, ls->d->next);
}
