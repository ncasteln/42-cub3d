/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/01/16 01:34:48 by mrubina          ###   ########.fr       */
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

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

//constants
# define WIN_W 1600
# define WIN_H 1200
#define TEX_W 64
#define TEX_H 64
#define VERTICAL 0
#define HORIZONTAL 1

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
typedef struct	s_rc {

	double			pos_x; //player position X
	double			pos_y; //player position Y
	double			dir_x; // look direction
	double			dir_y;
	double			plane_x; // camera plane
	double			plane_y;
	int				map_x; //square coordinates - left upper side of the sqare
	int				map_y;
	double			side_dist_x; // distance from the current position to next x side
	double			side_dist_y; // distance from the current position to next y side
	double			delta_dist_x; // length from one x side to the  next
	double			delta_dist_y; // length from one y side to the  next
	int				hit; //0 if the ray didn't hit a wall
	int				step_x; //raycasting step
	int				step_y;
	int				side;
	int				line_h;
	double			wall_dist;
	double			wall_x;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double	tex_pos;
	uint32_t		w_color;
	mlx_texture_t *tex[4];
	int	tex_h;
	int tex_w;
}	t_rc;


typedef struct s_cub3d
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	mlx_image_t*	img1;
	t_assets	*assets;
	char		**map;
	size_t		n_rows;
	size_t		n_col;
	char		*line;
	t_player	*p;
	t_rc	*rc;
}	t_cub3d;

typedef struct s_dvector
{
	double x;
	double y;
}	t_dvect;

//parameters for drawing
typedef struct s_draw
{
	mlx_texture_t* tex;
	//t_dvect *raydir
	int start;
	int end;
	int tex_x;
	int tex_y;
	int tex_w;
	int tex_h;
}	t_draw;

typedef struct s_ivector
{
	int x;
	int y;
}	t_ivect;

#endif
