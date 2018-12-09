/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:27:56 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/29 12:27:59 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void	sort_int_tab(int *tab, int size)
{
	int		i;
	int		swap;
	int		l;

	i = 0;
	if (!tab || !size)
		return ;
	while (i < size)
	{
		l = 0;
		while (l + i < size)
		{
			if (tab[i] > tab[l + i])
			{
				swap = tab[l + i];
				tab[l + i] = tab[i];
				tab[i] = swap;
			}
			l++;
			if (l + i == size)
				i++;
		}
	}
}

void	sort(t_m *m, t_d *d)
{
	t_m		tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < d->decision_size)
	{
		j = 0;
		while (++j + i < d->decision_size)
		{
			if (m[i].path_size > m[i + j].path_size)
			{
				tmp = m[i];
				m[i] = m[i + j];
				m[i + j] = tmp;
			}
		}
	}
}

void	sort_dec(t_d *d)
{
	while (d)
	{
		sort_int_tab(d->decision, d->decision_size);
		d = d->next;
	}
}
