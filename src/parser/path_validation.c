/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:17:39 by nico              #+#    #+#             */
/*   Updated: 2023/12/25 19:26:04 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	The map in which the player can walk has to be enclosed by walls (1). It is
	still possible that in this portion of map, there are empty spaces.
	Valid map.		Valid map.		Invalid map.
	111111111111	111111111111	111111111111
	1N0000000001	1N0000000001	1N000000000
	100      001	100      001	100      00
	100000000001	100000000001	10000000000
	111111111111	111111111111	111111111111
	  00000000
	    0000
*/
void	path_validation(t_cub3d *data)
{
	
}
