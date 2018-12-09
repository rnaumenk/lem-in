/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 19:07:10 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:26:36 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		initialize_all(t_s *ls)
{
	ls->input = 0;
	ls->start = 0;
	ls->end = 0;
	ls->r = NULL;
	ls->ant_number = 0;
	ls->ant_num_found = 0;
	ls->room_quantity = 0;
	ls->link_found = 0;
	ls->max_paths = 0;
	ls->path_found = 0;
	ls->max_path_size = 0;
	ls->d = NULL;
	ls->dec_found = 0;
	ls->input_lines = 0;
	ls->arg1 = 0;
	ls->arg2 = 0;
	ls->arg3 = 0;
	ls->arg4 = 0;
	ls->fullfilled = 0;
}

static void		save_the_input(t_s *ls)
{
	char	*temp;

	if (!ls->input)
	{
		if (!(ls->input = (char*)ft_memalloc(sizeof(char) *
			(ft_strlen(ls->line) + 3))))
			error(ls, 1);
		ft_memcpy(ls->input, ls->line, ft_strlen(ls->line));
	}
	else
	{
		temp = ls->input;
		if (!(ls->input = ft_strjoin(ls->input, ls->line)))
			error(ls, 1);
		ft_strdel(&temp);
		temp = ls->input;
		if (!(ls->input = (char*)ft_memalloc(sizeof(char) *
			(ft_strlen(temp) + 3))))
			error(ls, 1);
		ft_memcpy(ls->input, temp, ft_strlen(temp));
		ft_strdel(&temp);
	}
	ls->input[ft_strlen(ls->input)] = '\n';
	ls->input[ft_strlen(ls->input) + 1] = '\0';
}

static void		parse_args(t_s *ls, char *s)
{
	if (!s)
		return ;
	if (*s != '-' || !*(s + 1))
	{
		ft_printf("usage: ./lem-in (-[d,p,c,e])\n");
		exit(0);
	}
	while (*++s)
	{
		if (*s == 'p')
			ls->arg1 = 1;
		else if (*s == 'd')
			ls->arg2 = 1;
		else if (*s == 'c')
			ls->arg3 = 1;
		else if (*s == 'e')
			ls->arg4 = 1;
		else
		{
			ft_printf("usage: ./lem-in (-[d,p,c,e])\n");
			exit(0);
		}
	}
}

void			try_to_finish(t_s *ls)
{
	solve_this_shit(ls);
	ft_printf("%s\n", ls->input);
	move_this_shit(ls);
}

int				main(int argc, char **argv)
{
	t_s		ls;

	initialize_all(&ls);
	if (argc <= 2)
		parse_args(&ls, argc == 2 ? argv[1] : NULL);
	while (get_next_line(0, &ls.line) == 1)
	{
		ls.input_lines++;
		if (!ls.line[0])
			error(&ls, 16);
		validation(&ls);
		if ((ls.start == 1 || ls.end == 1) && !ls.ant_num_found)
			error(&ls, 12);
		if (ls.ant_number > 40000)
			error(&ls, 23);
		save_the_input(&ls);
		ft_strdel(&ls.line);
	}
	if (!ls.link_found)
		error(&ls, 17);
	ls.fullfilled = 1;
	try_to_finish(&ls);
	return (0);
}
