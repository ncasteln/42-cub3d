/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/01/16 02:24:33 by mrubina          ###   ########.fr       */
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
static void first_intersec(t_rc *rc, t_dvect *raydir)
{
	if (raydir->x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->delta_dist_x;
	}
	if (raydir->y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->delta_dist_y;
	}
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
static void ray_init(t_rc *rc, t_dvect *raydir, int pixel_x)
{
	double	cam_x;
	cam_x = 2 * pixel_x / ((double) WIN_W) - 1;

	raydir->x = rc->dir_x + rc->plane_x * cam_x;
	raydir->y = rc->dir_y + rc->plane_y * cam_x;
	rc->delta_dist_x = fabs(1 / raydir->x);
	rc->delta_dist_y = fabs(1 / raydir->y);
	rc->map_x = (int) rc->pos_x;
	rc->map_y = (int) rc->pos_y;
	first_intersec(rc, raydir);
}

/*
propagates the ray until it hits a wall
 */
static void find_hit(t_cub3d *data)
{
	while (data->rc->hit == 0)
	{
		if (data->rc->side_dist_x < data->rc->side_dist_y)
		{
			data->rc->side_dist_x += data->rc->delta_dist_x;
			data->rc->map_x += data->rc->step_x;
			data->rc->side = VERTICAL;
		}
		else
		{
			data->rc->side_dist_y += data->rc->delta_dist_y;
			data->rc->map_y += data->rc->step_y;
			data->rc->side = HORIZONTAL;
		}
		if (data->map[data->rc->map_y][data->rc->map_x] == 49)
			data->rc->hit = 1;
	}
	data->rc->hit = 0;
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

static mlx_texture_t* select_texture(t_cub3d *data, t_dvect *raydir)
{
	if (data->rc->side == HORIZONTAL)
	{
		if (raydir->y >= 0)
			return (data->rc->tex[0]);
		else if (raydir->y < 0)
			return (data->rc->tex[2]);
	}
	else
	{
		if (raydir->x >= 0)
			return (data->rc->tex[1]);
		else if (raydir->x < 0)
			return (data->rc->tex[3]);
	}
	return (NULL);
}

static void set_draw(t_rc *rc)
{
	rc->line_h = (int)(WIN_H / rc->wall_dist);
	rc->draw_start = WIN_H / 2 - rc->line_h / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = WIN_H / 2 + rc->line_h / 2;
	if (rc->draw_end >= WIN_H)
		rc->draw_end = WIN_H;
}

/*
prints a vertical line based on a texture
 */
static void putline(t_cub3d *data, int x, int draw_start, int draw_end, t_dvect *raydir, mlx_texture_t* tex)
{
	int y;
	int tex_y;
	double step;
	
	step = 1.0 * data->rc->tex_h / data->rc->line_h;
	data->rc->tex_pos = (data->rc->draw_start - WIN_H / 2 + data->rc->line_h / 2) * step;
	y = 0;
	while (y >=0 && y < WIN_H)
	{
		if (y >= draw_start && y <= draw_end)
		{
			tex_y = (int) data->rc->tex_pos & (data->rc->tex_h - 1);
			data->rc->tex_pos += step;
			data->rc->w_color = getpixcol(&tex->pixels[(tex_y * data->rc->tex_w + data->rc->tex_x)*4]);
			mlx_put_pixel(data->img, x, y, data->rc->w_color);
		}
		else if (y < draw_start)
			mlx_put_pixel(data->img, x, y, data->assets->c);
		else if (y > draw_end)
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
	t_dvect raydir;
	int pixel_x;
	mlx_texture_t* tex;

	pixel_x = 0;
	while (pixel_x < WIN_W)
	{
		ray_init(data->rc, &raydir, pixel_x);
		find_hit(data);
		if (data->rc->side == VERTICAL)
		{
			data->rc->wall_dist = data->rc->side_dist_x - data->rc->delta_dist_x;
			data->rc->wall_x = data->rc->pos_y + data->rc->wall_dist * raydir.y;
		}
		else
		{
			data->rc->wall_dist = data->rc->side_dist_y - data->rc->delta_dist_y;
			data->rc->wall_x = data->rc->pos_x + data->rc->wall_dist * raydir.x;
		}
		tex = select_texture(data, &raydir);
		//texture x
		data->rc->wall_x -= floor(data->rc->wall_x);
		data->rc->tex_x = (int)(data->rc->wall_x * (double)data->rc->tex_w);
		//printf("fgg %d \n", data->rc->tex_w);
		//exit(0);
		data->rc->tex_h = tex->height;
		data->rc->tex_w = tex->width;
		if (data->rc->side == VERTICAL && raydir.x > 0)
			data->rc->tex_x = data->rc->tex_w - data->rc->tex_x - 1;
		if (data->rc->side == HORIZONTAL && raydir.y < 0)
			data->rc->tex_x = data->rc->tex_w - data->rc->tex_x - 1;
		set_draw(data->rc);
		putline(data, pixel_x, data->rc->draw_start, data->rc->draw_end, &raydir, tex);
		//vert_line(data, data->rc->pixel_x, data->rc->draw_start, data->rc->draw_end);
		pixel_x++;
	}
}