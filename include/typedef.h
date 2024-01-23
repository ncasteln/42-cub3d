/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/01/23 20:34:19 by mrubina          ###   ########.fr       */
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
	char		*no;
	char		*ea;
	char		*so;
	char		*we;
	uint32_t	f;
	uint32_t	c;
}	t_assets;

typedef struct s_dvector
{
	double x;
	double y;
}	t_dvect;

typedef struct s_ivector
{
	int x;
	int y;
}	t_ivect;

// t_dvect			pos; // character position
// 	t_dvect			dir; // look direction
// 	t_dvect			plane; //camera plane
// 	t_ivect		map;	//square coordinates - left upper side of the sqare
typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
	t_dvect	pos;
	t_dvect	dirv;
	t_dvect	plane;
}	t_player;

//constants

# define WIN_W 1600
# define WIN_H 1200
#define NORTH_SOUTH 1
#define WEST_EAST 0
#define X 0
#define Y 1

//textures array indices
#define NO 0
#define WE 1
#define SO 2
#define EA 3


# define RED 0x990000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FF77
# define ORANGE 0xDD7700FF
# define WHITE 0xFFFFFFFF
# define WALLC WHITE

# define FORWARD 100
# define BACK 200
# define RIGHT 300
# define LEFT 400

//structures

typedef struct s_cub3d
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	mlx_image_t*	img1;
	mlx_texture_t	*tex[5];
	t_assets	*assets;
	char		**map;
	size_t		n_rows;
	size_t		n_col;
	char		*line;
	t_player	*p;
}	t_cub3d;

/* variables related to raycasting calculation
ray direction
distance from the current position to next x/y side
length from one x/y side to the next
distance from the player to the wall
*/
typedef struct s_raycast
{
	t_dvect	raydir;
	t_dvect	ray_len;
	t_dvect	ray_delta;
	double	wall_dist;
	double	wall_x;
	int		hit; //0 if the ray didn't hit a wall
	int		wall_dir;//wall direction NORTH_SOUTH or WEST_EAST
	int		line_h; //visible wall height for pixel_x
	int		tex_x;
	int		line_start;
	int		line_end;
	int		b_size;
	t_ivect	ray;
}	t_raycast;

typedef struct s_ftile
{
	double dist;
	double delta;
	int bottom;
	int h;
}	t_ftile;

#endif
