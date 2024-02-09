/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:30:48 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/09 08:46:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* sets some door parameters
	position of the door left and right edges
	as seen when the player stands facing the door
	direction // sides the door is facing
	sets the door as closed
*/
void set_door(int n, int y, int x, t_cub3d *data)
{
	 //printf("int xy %d %d \n", x, y);
	if (data->map[y][x - 1] == '1' && data->map[y][x + 1] == '1')
	{
		// printf("door start before %f %f \n", data->sprite[n].door_left_edge.x, data->sprite[n].door_left_edge.y);
		// printf("door end before %f %f \n", data->sprite[n].door_right_edge.x, data->sprite[n].door_right_edge.y);
		data->sprite[n].door_left_edge.x = x; //6 +
		data->sprite[n].door_right_edge.x = x + 0.999; //6.99
		data->sprite[n].door_left_edge.y = y + 0.5;  //2.5
		data->sprite[n].door_right_edge.y = y + 0.5;
		data->sprite[n].dir = NORTH_SOUTH;
	}
	else if (data->map[y - 1][x] == '1' && data->map[y + 1][x] == '1')
	{
		data->sprite[n].door_left_edge.y = y;
		data->sprite[n].door_right_edge.y = y + 0.999;
		data->sprite[n].door_left_edge.x = x + 0.5;
		data->sprite[n].door_right_edge.x = x + 0.5;
		data->sprite[n].dir = WEST_EAST;
	}
	data->sprite[n].isopen = CLOSED;
	// printf("st %f %f \n", data->sprite[n].door_left_edge.x, data->sprite[n].door_left_edge.y);
	// printf("end %f %f \n", data->sprite[n].door_right_edge.x, data->sprite[n].door_right_edge.y);
}

void	set_sprite(int n, int y, int x, t_cub3d *data)
{
	data->sprite[n].c = data->map[y][x];
	data->sprite[n].y = y;
	data->sprite[n].x = x;
	data->sprite[n].dist = -1;
	if (data->sprite[n].c == 'D')
		set_door(n, y, x, data);
	// data->sprite[n].dist = rand(); // remove, addedto test the bubblesort
}

/* sets squared distance
from the sprite to the current position of the player */
void	set_dist(t_cub3d *data)
{
	int	n;
	n = 0;
	while (n < data->n_total_sprites)
	{
		data->sprite[n].dist = sprite_dist_sq(data->sprite[n], data->p->pos);
		n++;
	}
}

//creates sprites at the start
void	create_sprite_list(t_cub3d *data)
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
			if (data->map[y][x] == 'H' || data->map[y][x] == '$' || data->map[y][x] == 'D')
			{
				set_sprite(n, y, x, data);
				n++;
			}
			x++;
		}
		y++;
	}
}

void	bubble(t_sprite *sprite, int n)
{
	t_sprite	temp;
	int			swapped;
	int			i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 1;
		while (i <= n - 1)
		{
			if (sprite[i - 1].dist < sprite[i].dist)
			{
				temp = sprite[i - 1];
				sprite[i - 1] = sprite[i];
				sprite[i] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

/*
	Holes and are considered SPRITES! So in an case the function runs, and it'll
	add eventually other BONUS sprites (included doors) in case the bonus
	version of the program is compiled.

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
	data->n_total_sprites = data->n_d + data->n_h + data->n_s;
	if (data->n_total_sprites)
	{
		data->sprite = ft_calloc(data->n_total_sprites, sizeof(t_sprite));
		if (!data->sprite)
			err_free_exit("create_sprite", data, errno);
	}
	create_sprite_list(data);
}
