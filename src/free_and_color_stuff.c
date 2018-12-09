/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:13:01 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/05/30 13:13:06 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void	free_split(char ***temp)
{
	int		i;
	char	**split;

	split = *temp;
	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
}

void	choose_the_color(t_s *ls, int a, char *s)
{
	if (ls->arg3 == 1)
	{
		if (a % 7 == 1)
			ft_printf("%s", KRED);
		else if (a % 7 == 2)
			ft_printf("%s", KGRN);
		else if (a % 7 == 3)
			ft_printf("%s", KYEL);
		else if (a % 7 == 4)
			ft_printf("%s", KBLU);
		else if (a % 7 == 5)
			ft_printf("%s", KMAG);
		else if (a % 7 == 6)
			ft_printf("%s", KCYN);
		else if (a % 7 == 0)
			ft_printf("%s", KWHT);
		else
			ft_printf("%s", KNRM);
	}
	ft_printf("L%d-%s", a, s);
}
