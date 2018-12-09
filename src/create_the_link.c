/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_the_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:25:59 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:26:02 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static int		check_if_repeat(int l, t_r *link)
{
	int		i;

	i = -1;
	while (++i < link->link_size)
	{
		if (link->link[i] == l)
			return (1);
	}
	return (0);
}

static void		add_the_link(t_s *ls, t_r *temp, int l)
{
	int		*tmp;

	if (!temp->link_size)
	{
		if (!(temp->link = (int*)malloc(sizeof(int))))
			error(ls, 1);
		temp->link[0] = l;
		temp->link_size++;
	}
	else
	{
		if (!check_if_repeat(l, temp))
		{
			tmp = temp->link;
			if (!(temp->link = (int*)malloc(sizeof(int) * temp->link_size + 1)))
				error(ls, 1);
			ft_memcpy(temp->link, tmp, (size_t)temp->link_size * 4);
			free(tmp);
			temp->link[temp->link_size] = l;
			temp->link_size++;
		}
	}
}

static void		link_them(t_s *ls, int l1, int l2)
{
	int		found;
	t_r		*temp;

	temp = ls->r;
	found = 0;
	while (temp && found != 2)
	{
		if (temp->index == l1)
		{
			add_the_link(ls, temp, l2);
			found++;
		}
		else if (temp->index == l2)
		{
			add_the_link(ls, temp, l1);
			found++;
		}
		temp = temp->next;
	}
}

static void		find_the_index(t_s *ls, char **split)
{
	t_r		*temp;
	int		l1;
	int		l2;

	temp = ls->r;
	l1 = -1;
	l2 = -1;
	while (temp)
	{
		if (!ft_strcmp(split[0], temp->name))
			l1 = temp->index;
		if (!ft_strcmp(split[1], temp->name))
			l2 = temp->index;
		temp = temp->next;
	}
	if (l1 == l2 || l1 < 0 || l2 < 0)
		error(ls, 2);
	link_them(ls, l1, l2);
}

void			create_the_link(t_s *ls)
{
	char	**split;
	int		i;
	t_r		*start;
	t_r		*end;

	start = ls->r;
	end = ls->r;
	while (start && start->start != 1)
		start = start->next;
	while (end && end->end != 1)
		end = end->next;
	if (!end || !start || !ls->r)
		error(ls, (!ls->r ? 25 : 18));
	if (!(split = ft_strsplit(ls->line, '-')))
		error(ls, 3);
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
		error(ls, 4);
	find_the_index(ls, split);
	free_split(&split);
	ls->link_found = 1;
}
