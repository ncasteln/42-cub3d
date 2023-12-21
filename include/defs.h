/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:53 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/21 22:02:14 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

//constants
# define WIN_W 640
# define WIN_H 480
# define MAP_W 24
# define MAP_H 24

# define RED 0x990000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FF77
# define ORANGE 0xDD7700FF
# define WHITE 0xFFFFFFFF

//structures

typedef struct s_data {
	mlx_t* mlx;
	mlx_image_t* img;
	double posX; //player position X
	double posY; //player position Y
	double dirX; // look direction
	double dirY;
	double rayDirX; // ray direction
	double rayDirY;
	double planeX; // camera plane
	double planeY;
	double time; // current frame
	double oldTime; // previous frame
	int x; //pixel in camera space from 0 to game window width
	int mapX; //square coordinates - left upper side of the sqare
	int mapY;
	double sideDistX; // distance from the current position to next x side
	double sideDistY; // distance from the current position to next y side
	double deltaDistX; // length from one x side to the  next
	double deltaDistY; // length from one y side to the  next
	double camX; //normalized x: from -1 to 1
	int hit; //0 if the ray didn't hit a wall
	int stepX; //raycasting step
	int stepY;
	int side;
	//struct Map map[MAP_H][MAP_W];
	int lineHeight;
	double wallDist;
	int drawStart;
	int drawEnd;
	int h;
	int sx;
}	t_data;


#endif