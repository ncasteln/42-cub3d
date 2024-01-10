/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/01/08 20:02:11 by mrubina          ###   ########.fr       */
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
# define WALLC WHITE

//structures
typedef struct	s_rcdata {

	double			pos_x; //player position X
	double			pos_y; //player position Y
	double			dir_x; // look direction
	double			dir_y;
	double			raydir_x; // ray direction
	double			raydir_y;
	double			plane_x; // camera plane
	double			plane_y;
	double			time; // current frame
	double			oldTime; // previous frame
	int				pixel_x; //pixel in camera space from 0 to game window width
	int				map_x; //square coordinates - left upper side of the sqare
	int				map_y;
	double			side_dist_x; // distance from the current position to next x side
	double			side_dist_y; // distance from the current position to next y side
	double			delta_dist_x; // length from one x side to the  next
	double			delta_dist_y; // length from one y side to the  next
	double			cam_x; //normalized x: from -1 to 1
	int				hit; //0 if the ray didn't hit a wall
	int				step_x; //raycasting step
	int				step_y;
	int				side;
	//struct Map map[MAP_H][MAP_W];
	int				line_h;
	double			wall_dist;
	int				draw_start;
	int				draw_end;
	int				h;
	uint32_t				w_color;
}	t_rcdata;


typedef struct s_cub3d
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	t_assets	*assets;
	char		**map;
	size_t		n_rows;
	size_t		n_col;
	char		*line;
	t_player	*p;
	t_rcdata	*rcdata;
}	t_cub3d;

#endif
