/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:28:16 by nico              #+#    #+#             */
/*   Updated: 2023/12/26 17:43:56 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_edge(int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_printf("-");
		i++;
	}
	ft_printf("--\n");
}

void	print_map(char **p, int	len)
{
	int	i;

	i = 0;
	if (p)
	{
		ft_printf("************* MAP *************\n");
		if (len)
			print_edge(len);
		while (p[i])
		{
			ft_printf("|%s|\n", p[i]);
			i++;
		}
		if (len)
			print_edge(len);
	}
}
