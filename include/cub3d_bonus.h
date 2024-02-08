/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:18:22 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/30 22:55:44 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

#include "typedef.h" // remove otherwise is in two places ?

#define MAP_PIXEL 10

void	check_behind_doors(t_cub3d *data, char **map_cpy);
void	minimap(t_cub3d *data);
//void	sprites(t_cub3d *data);

#endif
