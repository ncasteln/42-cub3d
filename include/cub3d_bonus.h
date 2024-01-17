/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:18:22 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/17 13:55:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

#include "typedef.h" // remove otherwise is in two places ?

#define MAP_PIXEL 1

void	draw_minimap(t_cub3d *data);
void	clear_minimap(t_cub3d *data);

#endif
