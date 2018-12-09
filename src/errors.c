/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:26:22 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:26:27 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void	error5(char **s, int n)
{
	if (n == 25)
		*s = "Use format: ant_num->rooms->links";
	else if (n == 26)
		*s = "##end/##start was indicated on the previous line";
	else
		*s = "Undefined error occured";
}

void	error4(char **s, int n, t_s *ls)
{
	if (n == 16)
		*s = "No input";
	else if (n == 17)
		*s = "No link";
	else if (n == 18)
		*s = "No start/end room indicated";
	else if (n == 19 && ls->fullfilled)
		*s = "No path found";
	else if (n == 19 && !ls->fullfilled)
		return ;
	else if (n == 20)
		*s = "Ant number != integer";
	else if (n == 21)
		*s = "Ant number is already indicated or whatever you meant";
	else if (n == 22)
		*s = "DEL ZERO(ES)";
	else if (n == 23)
		*s =
	"This algorithm may cause the stackoverflow with \
such a huge number of ants :( try ants <= 40000";
	else if (n == 24)
		*s = "Ant number <= 0";
	else
		error5(s, n);
}

void	error3(char **s, int n, t_s *ls)
{
	if (n == 5)
		*s = "Coord/coords != integer";
	else if (n == 6)
		*s = "Room overlap";
	else if (n == 7)
		*s = "Same rooms' names";
	else if (n == 8)
		*s = "##start or ##end???";
	else if (n == 9)
		*s = "##end cmd is repeated";
	else if (n == 10)
		*s = "##start cmd is repeated";
	else if (n == 11)
		*s = "Room name starts with 'L'";
	else if (n == 12)
		*s = "Give me ant number first";
	else if (n == 13)
		*s = "You try to create a room in the section for links";
	else if (n == 14)
		*s = "Some huge or negative number for coords given";
	else if (n == 15)
		*s = "WTF line is that?";
	else
		error4(s, n, ls);
}

void	error2(char **s, int n, t_s *ls)
{
	if (n == 2)
		*s = "Link to the room that doesn't exist or to itself";
	else if (n == 3)
		*s = "Split error";
	else if (n == 4)
		*s = "Incomplete link";
	else
		error3(s, n, ls);
	ft_printf("Error #%d. %s (line: %d)\n", n, *s, ls->input_lines);
	exit(0);
}

void	error(t_s *ls, int n)
{
	char	*s;

	if (!ls->fullfilled && ls->link_found)
	{
		ls->fullfilled = 1;
		try_to_finish(ls);
		exit(0);
	}
	if (ls->arg3)
		ft_printf("%s", KRED);
	if (n == 1)
	{
		write(1, "Memory allocation error\n", 24);
		exit(0);
	}
	else if (ls->arg4 == 0)
	{
		write(1, "ERROR\n", 6);
		exit(0);
	}
	error2(&s, n, ls);
}
