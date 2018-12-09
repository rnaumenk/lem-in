/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:28:10 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:28:16 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		ant_number(t_s *ls)
{
	int		i;

	i = -1;
	if (!ls->line[0])
		error(ls, 12);
	if (ls->ant_num_found == 1)
		error(ls, 21);
	while (ls->line[++i])
	{
		if (ls->line[i] == '-')
			error(ls, 24);
		if (ls->line[i] < 48 || ls->line[i] > 57)
			error(ls, 20);
	}
	if (ft_strlen(ls->line) > 10 || (ft_atoi(ls->line) < 0 &&
		ls->line[0] != '-'))
		error(ls, 23);
	if (ls->line[0] == 48 && ls->line[i - 1] != 48)
		error(ls, 22);
	ls->ant_number = ft_atoi(ls->line);
	if (ls->ant_number == 0)
		error(ls, 24);
	ls->ant_num_found = 1;
}

static int		parse_the_string(t_s *ls)
{
	int		space;
	int		def;
	int		i;

	space = 0;
	def = 0;
	i = -1;
	while (ls->line[++i])
	{
		if (ls->line[i] == 32)
			space++;
		else if (ls->line[i] == '-')
			def++;
	}
	if (space == 2)
		return (1);
	else if (!space && def == 1 && ls->line[0] != '-' && ls->line[i - 1] != '-')
		return (2);
	else if (!space && (!def || (ls->line[0] == '-' && def == 1)))
		return (-1);
	error(ls, 15);
	return (0);
}

static void		cmd_processing(t_s *ls)
{
	if (!ft_strcmp(ls->line + 2, "start"))
	{
		if (!ls->start && (!ls->end || ls->end == -1))
			ls->start = 1;
		else
			error(ls, (!ls->start && ls->end ? 8 : 10));
	}
	else if (!ft_strcmp(ls->line + 2, "end"))
	{
		if (!ls->end && (!ls->start || ls->start == -1))
			ls->end = 1;
		else
			error(ls, (!ls->end && ls->start ? 8 : 9));
	}
	else if (ls->end == 1 || ls->start == 1)
		error(ls, 26);
}

void			validation(t_s *ls)
{
	int		l;

	if (ls->line[0] == '#' && ls->line[1] != '#')
		return ;
	else if (ls->line[0] == '#' && ls->line[1] == '#')
		cmd_processing(ls);
	else if ((l = parse_the_string(ls)) == 1)
		create_the_room(ls);
	else if (l == 2)
		create_the_link(ls);
	else
		ant_number(ls);
}
