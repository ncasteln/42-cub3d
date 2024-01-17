/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/17 21:06:36 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
functions for raycasting algorithm
 */

/*
Some expanations, for now incomplete:
	We have several spaces and each space has several coordinate systems
		1. Map space - this is a space where our player walks
	it has two coordinate systems:
		1.1 Integer coordinates
	first system is integer and based on squares
	for example we have a map 10x10 squares
	A square can be occupied or not occupied by the wall
	It's easy to say where is the wall on the map using integer coordinates
	for example we can put a column at (6, 7)
		1.2 Float point coordinates
	A player doesn't occupy the whole square and he can move inside it
	so it makes sense using float point coordinates to show his precise position
	if a player has integer coordinates (1,1) and he moves inside the square (1,1)
	his float coordinates can be (1.24, 1.76) for example
		2. Screen space - this is what out player sees and therefore our game screen shows
	it also has two types of coordinates:
		2.1 Integer (pixel) coordinates
	first system is integer pixel system
	if for example our game window is 640x480 pixels
	a pixel is going to have integer coordinates like (120,65)
		2.2 Float point coordinates
	float point coordinates are used to make vector manipulations easier
	we use it only for x-dimension here
	the left side of the window has x = -1, middle x = 0 right side - x = 1
	I call them normalized coordinates because it's similar
	to normalization process in math.
	Raycasting algorithm:
	Input (non-constant): palyer position, player look direction
	Output: the game screen shows what player sees
	for each x of the game screen we find the wall that the player faces,
	calculate the distance to that wall and its size
	and draw that wall
*/
//for each pixel line we calculate ray direction
// length of the ray between 2 closest integer x/y
		//map square where player is
			//init we start from player position
// calculate distance before the first intersection and the step

/*
calculates the length of the ray from its start (player position)
till the first intersection with x/y integer coordinate net
|         |/
|        /| - intersection with x
|       / |
|      /  |
|     /   |
|----/----|----- intersection with y
|   /     |
|  /      |
	ray start
calculation based on triangle proportion
 */
static void first_intersec(t_raycast *rc, t_player *p)
{
	if (rc->raydir.x < 0)
		rc->side_dist.x = (p->pos.x - p->x) * rc->delta_dist.x;
	else
		rc->side_dist.x = (p->x + 1.0 - p->pos.x) * rc->delta_dist.x;
	if (rc->raydir.y < 0)
		rc->side_dist.y = (p->pos.y - p->y) * rc->delta_dist.y;
	else
		rc->side_dist.y = (p->y + 1.0 - p->pos.y) * rc->delta_dist.y;
}

/*
calculates some ray parameters

|     | / (ray)
|     |/
|     /
|----/|----- y
|   / |
|  /  |
|-/---|----- y+1
|/    |
x     x+1

1. Camera space FP(float point) coordinate (cam_x)
2. Ray direction vector (raydir_x, raydir_y)
3. Ray length between two adjacent integer x/y
4. Map space integer coordinates
5. First intersec parameters
 */
static void ray_init(int pixel_x, t_raycast *rc, t_player *p)
{
	double	cam_x;

	cam_x = 2 * pixel_x / ((double) WIN_W) - 1;
	rc->raydir.x = p->dirv.x + p->plane.x * cam_x;
	rc->raydir.y = p->dirv.y + p->plane.y * cam_x;
	rc->delta_dist.x = fabs(1 / rc->raydir.x);
	rc->delta_dist.y = fabs(1 / rc->raydir.y);
	p->x = (int) p->pos.x;
	p->y = (int) p->pos.y;
	first_intersec(rc, p);
}

/*
propagates the ray until it hits a wall
 */
static void find_hit(t_cub3d *data, t_raycast *rc)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			data->p->x += sign(rc->raydir.x);
			rc->side = VERTICAL;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			data->p->y += sign(rc->raydir.y);
			rc->side = HORIZONTAL;
		}
		if (data->map[data->p->y][data->p->x] == 49)
			rc->hit = 1;
	}
	
}


/*
Selects a texture
if a ray with positive y (ray direction vector) hits a horizontal wall
it means that the wall faces North and we use the  "North texture"
\    /
 \  /
__\/_________
similarly for other cases
 */
static mlx_texture_t* select_texture(t_cub3d *data, t_dvect *raydir, int side)
{
	if (side == HORIZONTAL)
	{
		if (raydir->y >= 0)
			return (data->tex[0]);
		else if (raydir->y < 0)
			return (data->tex[2]);
	}
	else
	{
		if (raydir->x >= 0)
			return (data->tex[1]);
		else if (raydir->x < 0)
			return (data->tex[3]);
	}
	return (NULL);
}

static void set_draw(t_raycast *rc)
{
	rc->line_h = (int)(WIN_H / rc->wall_dist);
	rc->line_start = WIN_H / 2 - rc->line_h / 2;
	if (rc->line_start < 0)
		rc->line_start = 0;
	rc->line_end = WIN_H / 2 + rc->line_h / 2;
	if (rc->line_end >= WIN_H)
		rc->line_end = WIN_H;
}

/*
prints a vertical line based on a texture
color that we want to use for a pixel depends on

 */
static void putline(t_cub3d *data, int x, mlx_texture_t* tex, t_raycast *rc)
{
	int			y;
	int			tex_y;
	double		step;
	double		tex_pos;
	uint32_t	w_color;

	step = 1.0 * tex->height / rc->line_h;//we move along th texture height with this step
	tex_pos = (rc->line_start - WIN_H / 2 + rc->line_h / 2) * step;
	y = 0;
	while (y >=0 && y < WIN_H)
	{
		if (y >= rc->line_start && y <= rc->line_end)
		{
			tex_y = (int) tex_pos & (tex->height - 1);
			tex_pos += step;
			w_color = getpixcol(&tex->pixels[(tex_y * tex->width + rc->tex_x)*4]);
			mlx_put_pixel(data->img, x, y, w_color);
		}
		else if (y < rc->line_start)
			mlx_put_pixel(data->img, x, y, data->assets->c);
		else if (y > rc->line_end)
			mlx_put_pixel(data->img, x, y, data->assets->f);
		y++;
	}
}

/*
for each horizontal pixel we take a ray
that should be projected on the screen for that point
we find where the ray hits the wall and
calculte the distance to this wall
this allows us to draw the wall
 */
void raycasting(t_cub3d *data)
{
	int pixel_x;
	mlx_texture_t* tex;
	t_raycast rc;

	pixel_x = 0;
	while (pixel_x < WIN_W)
	{
		ray_init(pixel_x, &rc, data->p);
		find_hit(data,  &rc);
		if (rc.side == VERTICAL)
		{
			rc.wall_dist = rc.side_dist.x - rc.delta_dist.x;
			rc.wall_x = data->p->pos.y + rc.wall_dist * rc.raydir.y;
		}
		else
		{
			rc.wall_dist = rc.side_dist.y - rc.delta_dist.y;
			rc.wall_x = data->p->pos.x + rc.wall_dist * rc.raydir.x;
		}
		tex = select_texture(data, &rc.raydir, rc.side);
		//texture x
		rc.wall_x -= floor(rc.wall_x);
		rc.tex_x = (int)(rc.wall_x * (double)tex->width);

		if (rc.side == VERTICAL && rc.raydir.x > 0)
			rc.tex_x = tex->width - rc.tex_x - 1;
		if (rc.side == HORIZONTAL && rc.raydir.y < 0)
			rc.tex_x = tex->width - rc.tex_x - 1;
		set_draw(&rc);
		putline(data, pixel_x, tex, &rc);
		pixel_x++;
	}
}
