/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:30:48 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/21 23:14:44 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* sets some door parameters
	position of the door left and right edges
	as seen when the player stands facing the door
	direction // sides the door is facing
	sets the door as closed
*/
static void	set_door(int n, int y, int x, t_cub3d *data)
{
	data->sprite[n].tex_i = D;
	if (read_map(data, y, x - 1) == '1' && read_map(data, y, x + 1) == '1')
	{
		data->sprite[n].door_left_edge.x = x;
		data->sprite[n].door_right_edge.x = x + 0.999;
		data->sprite[n].door_left_edge.y = y + 0.5;
		data->sprite[n].door_right_edge.y = y + 0.5;
		data->sprite[n].dir = NORTH_SOUTH;
	}
	else if (read_map(data, y - 1, x) == '1' && read_map(data, y + 1, x) == '1')
	{
		data->sprite[n].door_left_edge.y = y;
		data->sprite[n].door_right_edge.y = y + 0.999;
		data->sprite[n].door_left_edge.x = x + 0.5;
		data->sprite[n].door_right_edge.x = x + 0.5;
		data->sprite[n].dir = WEST_EAST;
	}
	data->sprite[n].isopen = CLOSED;
}

static void	set_sprite(int n, int y, int x, t_cub3d *data)
{
	data->sprite[n].c = data->map[y][x];
	data->sprite[n].y = y + 0.5;
	data->sprite[n].x = x + 0.5;
	data->sprite[n].dist = -1;
	if (data->sprite[n].c == 'H')
		data->sprite[n].tex_i = H;
	if (data->sprite[n].c == 'D')
		set_door(n, y, x, data);
}

//creates sprites at the start
static void	create_sprite_list(t_cub3d *data)
{
	int	y;
	int	x;
	int	n;

	y = 0;
	n = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'H' || data->map[y][x] == 'D')
			{
				set_sprite(n, y, x, data);
				n++;
			}
			x++;
		}
		y++;
	}
}

/*
	Holes and Doors are considered SPRITES (Holes are handled in both
	mandatory and bonus version, doors only in bonus)

	) Create sprite list
	) Calculate the dist of each sprite
	) Sort by distance
	) Projection of the sprite (2x2 matrix)
	) Calculate the size on the screen
	) Draws
*/

void	sprites(t_cub3d *data)
{
	count_sprites(data);
	data->n_total_sprites = data->n_d + data->n_h;
	if (data->n_total_sprites)
	{
		data->sprite = ft_calloc(data->n_total_sprites, sizeof(t_sprite));
		if (!data->sprite)
			err_free_exit("create_sprite", data, 0, errno);
	}
	create_sprite_list(data);
}
