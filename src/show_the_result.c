/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_the_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:46:27 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 14:46:31 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void		check_for_space(t_s *ls, t_m *m, int l)
{
	int		i;
	int		j;

	i = -1;
	while (++i < l)
	{
		j = -1;
		while (++j < m[i].path_size)
		{
			if (m[i].ant_index[j] > ls->min_ant_index)
			{
				ft_printf(" ");
				return ;
			}
		}
	}
	if ((ls->best_dec->direct || ls->best_dec->decision_size == 1) &&
		ls->min_ant_index < ls->ant_number)
		ft_printf(" ");
}

static void		output2(t_s *ls, t_m *m, int k, int l)
{
	int		i;
	int		j;

	while (ls->min_ant_index < k)
	{
		i = -1;
		while (++i < l)
		{
			j = -1;
			while (++j < m[i].path_size)
			{
				if (m[i].ant_index[j] == ls->min_ant_index)
				{
					choose_the_color(ls, ls->min_ant_index, m[i].path[j]);
					check_for_space(ls, m, l);
				}
			}
		}
		ls->min_ant_index++;
	}
	if (!(ls->best_dec->direct && k <= ls->ant_number))
		ft_printf("\n");
	if (k <= ls->ant_number || empty(m, l))
		go(ls, m, k, l);
}

static void		output(t_s *ls, t_m *m, int k, int l)
{
	int		i;
	int		j;

	ls->min_ant_index = ls->ant_number;
	i = -1;
	while (++i < l)
	{
		j = m[i].path_size;
		while (--j >= 0)
		{
			if (m[i].ant_index[j] != 0)
				ls->min_ant_index = (m[i].ant_index[j] < ls->min_ant_index ?
					m[i].ant_index[j] : ls->min_ant_index);
		}
	}
	output2(ls, m, k, l);
}

void			go(t_s *ls, t_m *m, long k, int l)
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
	j = -1;
	while (++j < l)
	{
		if (k <= ls->ant_number)
			m[j].ant_index[0] = k++;
	}
	output(ls, m, k, l);
}
