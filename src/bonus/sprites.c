/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:30:48 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/25 17:36:54 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_sprite(int n, int y, int x, t_cub3d *data)
{
	data->sprite[n].c = data->map[y][x];
	data->sprite[n].y = y;
	data->sprite[n].dist = rand();
	data->sprite[n].x = x;
	// data->sprite[n].dist = -1;
}

static void	create_sprite_list(t_cub3d *data, int total)
{
	int	y;
	int	x;
	int	n;

	data->sprite = ft_calloc(total, sizeof(t_sprite));
	if (!data->sprite)
		err_free_exit("create_sprite", data, errno);
	y = 0;
	n = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == ' ' || data->map[y][x] == '$' || data->map[y][x] == 'D')
			{
				set_sprite(n, y, x, data);
				n++;
			}
			x++;
		}
		y++;
	}
}

void	swap_ptr(void *p1, void *p2)
{
	void	*temp;

	temp = p1;
	p1 = p2;
	p2 = temp;
}

void	sort_sprite_by_distance(t_sprite *sprite, int total)
{
	int	i;
	int	j;
	double	curr;

	i = 1;
	while (i < total)
	{
		curr = sprite[i].dist;
		j = i - 1;
		while (j >= 0 && sprite[j].dist > curr)
		{
			sprite[j + 1].dist = sprite[j].dist;
			j -= 1;
		}
		sprite[j + 1].dist = curr;
		i++;
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
	// uint32_t	buff[WIN_H][WIN_W];
	// double		ZBuff[WIN_W];
	int	total;

	total = data->n_d + data->n_h + data->n_s;
	create_sprite_list(data, total);
	sort_sprite_by_distance(data->sprite, total);

	// int i = 0;
	// while (i < total)
	// {
	// 	printf("[%f] \n", data->sprite2[i].dist);
	// 	i++;
	// }

	// set_sprite_pos(&sprite, data);

	// i = 0;
	// while (i < data->n_sprites)
	// {
	// 	double posX = data->p->pos.x;
	// 	double posY = data->p->pos.y;
	// 	sprite[i].dist = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); // sqrt()?
	// 	i++;
	// }
}
