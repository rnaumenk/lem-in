/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_and_cmp_functs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:19:27 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 15:19:29 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

t_pa	*path_cpy(t_s *ls, t_pa *path, int k)
{
	t_pa	*new_path;

	if (!(new_path = (t_pa*)malloc(sizeof(t_pa))))
		error(ls, 1);
	new_path->index = (k == 1 ? ++ls->path_found : ls->path_found);
	new_path->path_size = path->path_size;
	if (!(new_path->path = (int*)malloc(sizeof(int) * new_path->path_size)))
		error(ls, 1);
	ft_memcpy(new_path->path, path->path, new_path->path_size * 4);
	new_path->next = NULL;
	return (new_path);
}

t_d		*dec_cpy(t_s *ls, t_d *d, int k)
{
	t_d		*new_d;

	if (!(new_d = (t_d*)malloc(sizeof(t_d))))
		error(ls, 1);
	if (!(new_d->decision = (int*)malloc(sizeof(int) * ls->max_paths)))
		error(ls, 1);
	new_d->index = (k == 1 ? ls->dec_found++ : ls->dec_found);
	new_d->decision_size = d->decision_size;
	new_d->direct = d->direct;
	ft_memcpy(new_d->decision, d->decision, d->decision_size * 4);
	new_d->next = NULL;
	return (new_d);
}

int		path_cmp(t_pa *p1, t_pa *p2)
{
	if (p1->path_size != p2->path_size)
		return (1);
	return (ft_memcmp(p1->path, p2->path, p1->path_size * 4));
}

int		dec_cmp(t_d *d1, t_d *d2)
{
	if (d1->decision_size != d2->decision_size)
		return (1);
	return (ft_memcmp(d1->decision, d2->decision, d1->decision_size * 4));
}
