/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:11:52 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 15:11:53 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static int		can_i_go(int i, t_pa *path)
{
	int		j;

	j = -1;
	while (++j < path->path_size)
	{
		if (path->path[j] == i)
			return (0);
	}
	return (1);
}

static void		create_new_path_nodes(t_s *ls, t_pa *path, t_r *room,
	t_pa *path_to_cmp)
{
	t_pa	*tmp;
	int		i;
	int		cp;

	tmp = path;
	i = -1;
	cp = 0;
	while (++i < room->link_size && room->end != 1)
	{
		if (can_i_go(room->link[i], path_to_cmp))
		{
			if (cp == 1)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = path_cpy(ls, path, 1);
				tmp = tmp->next;
			}
			cp = 1;
		}
	}
}

static void		fill_new_paths(t_s *ls, t_pa *path, t_r *room,
	t_pa *path_to_cmp)
{
	t_pa	*tmp;
	int		i;

	tmp = path;
	i = -1;
	while (++i < room->link_size && room->end != 1)
	{
		if (can_i_go(room->link[i], path_to_cmp))
		{
			find_the_path(ls, tmp, room, i);
			while (tmp && path_cmp(path_to_cmp, tmp))
				tmp = tmp->next;
		}
	}
}

void			find_the_path(t_s *ls, t_pa *path, t_r *start, int i)
{
	t_r		*room;
	t_pa	*path_to_cmp;
	int		*temp;

	room = ls->r;
	while (room->index != start->link[i])
		room = room->next;
	temp = path->path;
	if (!(path->path = (int*)malloc(sizeof(int) * ++path->path_size)))
		error(ls, 1);
	ft_memcpy(path->path, temp, (path->path_size - 1) * 4);
	free(temp);
	path->path[path->path_size - 1] = room->index;
	path_to_cmp = path_cpy(ls, path, 0);
	create_new_path_nodes(ls, path, room, path_to_cmp);
	fill_new_paths(ls, path, room, path_to_cmp);
	free(path_to_cmp->path);
	free(path_to_cmp);
}

void			find_all_possible(t_s *ls, int i)
{
	t_pa	*path;
	t_r		*start;

	start = ls->r;
	while (start && start->start != 1)
		start = start->next;
	if (!(ls->p = (t_pa*)malloc(sizeof(t_pa))))
		error(ls, 1);
	path = ls->p;
	new_path_initialization(ls, path, start);
	while (++i < start->link_size)
	{
		find_the_path(ls, path, start, i);
		if (i + 1 < start->link_size)
		{
			while (path->next)
				path = path->next;
			if (!(path->next = (t_pa*)malloc(sizeof(t_pa))))
				error(ls, 1);
			ls->path_found++;
			path = path->next;
			new_path_initialization(ls, path, start);
		}
	}
}
