/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_the_best_output.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:39:51 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 14:39:52 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		try_more(t_s *ls, t_m *m, long k, int l)
{
	int		j;

	j = -1;
	while (++j < l)
	{
		if (k <= ls->ant_number)
			m[j].ant_index[0] = k++;
		if (m[j].direct == 1)
			break ;
	}
	ls->steps++;
	if (k <= ls->ant_number || empty(m, l))
		trial(ls, m, k, l);
}

void			trial(t_s *ls, t_m *m, long k, int l)
{
	int		i;
	int		j;

	j = -1;
	while (++j < l)
	{
		i = m[j].path_size;
		while (--i >= 0)
		{
			if (i == m[j].path_size - 1)
				m[j].ant_index[i] = 0;
			else
			{
				m[j].ant_index[i + 1] = m[j].ant_index[i];
				m[j].ant_index[i] = 0;
			}
		}
	}
	try_more(ls, m, k, l);
}

int				calculate_the_best_output(t_s *ls, int b)
{
	t_d		*d;
	int		l;
	int		f;
	int		k;

	d = ls->d;
	k = -1;
	while (++k < ls->dec_found)
	{
		l = -1;
		while (++l < d->decision_size)
		{
			ls->steps = 0;
			trial(ls, ls->m[k], 1, l + 1);
			if (b > ls->steps)
			{
				b = ls->steps;
				f = l;
				ls->best_paths = k;
				ls->best_dec = d;
			}
		}
		d = d->next;
	}
	return (f + 1);
}
