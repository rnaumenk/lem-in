/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsortable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:31:36 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 15:31:38 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void			new_path_initialization(t_s *ls, t_pa *path, t_r *start)
{
	path->index = ls->path_found;
	path->path_size = 1;
	if (!(path->path = (int*)malloc(sizeof(int))))
		error(ls, 1);
	path->path[0] = start->index;
	path->next = NULL;
}

static int		check_crosses(t_pa *p1, t_pa *p2)
{
	int		i;
	int		j;

	if (p1->index == p2->index)
		return (1);
	i = 0;
	while (++i < p1->path_size - 1)
	{
		j = 0;
		while (++j < p2->path_size - 1)
		{
			if (p1->path[i] == p2->path[j])
				return (1);
		}
	}
	return (0);
}

int				cross_test(t_s *ls, t_d *d, t_pa *path)
{
	t_pa	*tmp;
	int		i;

	tmp = ls->p;
	while (tmp)
	{
		i = -1;
		while (++i < d->decision_size)
		{
			if (d->decision[i] == tmp->index && check_crosses(tmp, path))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int				empty(t_m *m, int l)
{
	int		i;
	int		j;

	i = -1;
	while (++i < l)
	{
		j = -1;
		while (++j < m[i].path_size - 1)
		{
			if (m[i].ant_index[j] != 0)
				return (1);
		}
	}
	return (0);
}
