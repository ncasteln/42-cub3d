/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:46:59 by nico              #+#    #+#             */
/*   Updated: 2023/12/24 20:50:00 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_assets(t_assets *assets)
{
	if (!assets)
		return ;
	ft_printf("--- ASSETS ---\n");
	if (assets->no)
		ft_printf("NO [%s]\n", assets->no);
	if (assets->ea)
		ft_printf("EA [%s]\n", assets->ea);
	if (assets->so)
		ft_printf("SO [%s]\n", assets->so);
	if (assets->we)
		ft_printf("WE [%s]\n", assets->we);
	if (assets->f)
		ft_printf("F [%s]\n", assets->f);
	if (assets->c)
		ft_printf("C [%s]\n", assets->c);
}
