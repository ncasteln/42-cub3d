/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/01/05 00:24:23 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

enum err
{
	E_ARGC = 107,
	E_INV_EXT,
	E_PARSE_ASSETS,
	E_DUP_ASSET,
	E_INV_ASSET,
	E_MISS_ASSET,
	E_INV_CHAR,
	E_INV_FORMAT,
	E_EMPTY_FILE,
	E_NO_MAP,
	E_DUP_PLAYER,
	E_NO_PLAYER,
	E_MAP_OPEN
};

typedef struct s_assets
{
	char	*no;
	char	*ea;
	char	*so;
	char	*we;
	char	*f;
	char	*c;
}	t_assets;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

//constants
# define WIN_W 640
# define WIN_H 480
# define MAP_W 13
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
	int pixelX; //pixel in camera space from 0 to game window width
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
}	t_data;


typedef struct s_cub3d
{
	t_assets	*assets;
	char		**map;
	size_t		n_rows;
	size_t		n_col;
	char		*line;
	t_player	*p;
	// t_raycast
}	t_cub3d;

#endif
