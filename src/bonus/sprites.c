/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:30:48 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/24 17:19:07 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_sprite(t_cub3d *data, int y, int x)
{
	t_sprite	*sprite;
	t_list		*node;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		err_free_exit("create_sprite", data, errno);
	sprite->c = data->map[y][x];
	sprite->y = y;
	sprite->x = x;
	sprite->dist = -1;
	node = ft_lstnew(sprite);
	if (!node)
		err_free_exit("create_sprite", data, errno);
	ft_lstadd_back(&data->sprite, node);
}

static void	create_sprite_list(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == ' '
				|| data->map[y][x] == '$'
				|| data->map[y][x] == 'D')
				create_sprite(data, y, x);
			x++;
		}
		y++;
	}
}

/*
	Holes and are considered SPRITES! So in an case the function runs, and it'll
	add eventually other BONUS sprites (included doors) in case the bonus
	version of the program is compiled.

	0) Calculate the dist of each sprite
	1) Projection of the sprite (2x2 matrix)
	2) Calculate the size on the screen
	3) Draws
*/
void	sprites(t_cub3d *data)
{
	// uint32_t	buff[WIN_H][WIN_W];
	// double		ZBuff[WIN_W];

	create_sprite_list(data);
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
