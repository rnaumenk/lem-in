/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_the_room.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:26:09 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:26:13 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		check_the_coords(t_s *ls, char **split)
{
	t_r		*temp;
	int		i;

	i = -1;
	while (split[1][++i])
	{
		if (split[1][i] < 48 || split[1][i] > 57)
			error(ls, 5);
	}
	i = -1;
	while (split[2][++i])
	{
		if (split[2][i] < 48 || split[2][i] > 57)
			error(ls, 5);
	}
	temp = ls->r;
	while (temp)
	{
		if (temp->x == ft_atoi(split[1]) && temp->y == ft_atoi(split[2]))
			error(ls, 6);
		temp = temp->next;
	}
}

static void		check_the_name(t_s *ls, char **split)
{
	t_r		*temp;

	temp = ls->r;
	while (temp)
	{
		if (!ft_strcmp(split[0], temp->name))
			error(ls, 7);
		temp = temp->next;
	}
}

static void		fill_the_data(t_s *ls, t_r *temp, char **split)
{
	temp->index = ls->room_quantity - 1;
	if (ls->start == 1)
	{
		temp->start = 1;
		ls->start = -1;
	}
	else
		temp->start = 0;
	if (ls->end == 1)
	{
		temp->end = 1;
		ls->end = -1;
		ls->end_index = temp->index;
	}
	else
		temp->end = 0;
	temp->name = ft_strdup(split[0]);
	if (temp->name[0] == 'L')
		error(ls, 11);
	temp->x = ft_atoi(split[1]);
	temp->y = ft_atoi(split[2]);
	temp->link_size = 0;
	temp->next = NULL;
}

static void		add_the_room(t_s *ls, char **split)
{
	t_r		*temp;

	temp = ls->r;
	if (!ls->r)
	{
		if (!(ls->r = (t_r*)malloc(sizeof(t_r))))
			error(ls, 1);
		temp = ls->r;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = (t_r*)malloc(sizeof(t_r))))
			error(ls, 1);
		temp = temp->next;
	}
	fill_the_data(ls, temp, split);
}

void			create_the_room(t_s *ls)
{
	char	**split;
	int		i;

	if (ls->link_found || !ls->ant_num_found)
		error(ls, (!ls->ant_num_found ? 12 : 13));
	if (!(split = ft_strsplit(ls->line, ' ')))
		error(ls, 3);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		error(ls, 15);
	i = 0;
	while (split[++i])
	{
		if (ft_strlen(split[i]) > 10 || ft_atoi(split[i]) < 0)
			error(ls, 14);
	}
	check_the_name(ls, split);
	check_the_coords(ls, split);
	++ls->room_quantity;
	add_the_room(ls, split);
	free_split(&split);
}
