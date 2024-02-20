/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/02/20 09:30:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

// ------------------------------------------------------------------ CONSTANTS
# define WIN_W 1600
# define WIN_H 1200
# define NORTH_SOUTH 1
# define WEST_EAST 0
# define X 0
# define Y 1
# define OPEN 0
# define CLOSED 1
# define OPENING 2
# define CLOSING 3

// ------------------------------------------------------------------- TEXTURES
# define NO 0
# define WE 1
# define SO 2
# define EA 3
# define H 4	// hole
# define D 5	// door

# define RED		0x990000FF
# define GREEN		0x00FF00FF
# define BLUE		0x0000FF77
# define ORANGE		0xDD7700FF
# define WHITE		0xFFFFFFFF
# define BLACK		0x000000FF
# define WALLC WHITE

# define FORWARD	100
# define BACK		200
# define RIGHT		300
# define LEFT		400

/* BONUS is the alternative version of the program which is compiled when the
user type 'make bonus' in the terminal. Otherwise, BONUS is set to 0 and some
future are not enabled in the code */
# ifndef BONUS
#  define BONUS 0
# endif
# define MINIMAP_PIXEL 10

// --------------------------------------------------------------------- ERRORS
enum e_err
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
	E_MAP_OPEN,
	E_INV_DOOR,
	E_MLX
};

// -------------------------------------------------------------------- STRUCTS
/*
	@param *d - doors
	@param *h - holes (white space inside wlakable map)
*/
typedef struct s_assets
{
	char		*no;
	char		*ea;
	char		*so;
	char		*we;
	uint32_t	f;
	uint32_t	c;
	char		*d;
	char		*h;
}	t_assets;

typedef struct s_dvector
{
	double	x;
	double	y;
}	t_dvect;

typedef struct s_ivector
{
	int	x;
	int	y;
}	t_ivect;

/*
	@param pos - position of the player
	@param dir - look direction of player
	@param plane - camera plane
	@param dirv - direction vector
*/
typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
	t_dvect	pos;
	t_dvect	dirv;
	t_dvect	plane;
}	t_player;

/*
	@param c - can be either D or H
	@param door_*_edge - filled only for the door
*/
typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
	char	c;
	int		tex_i;
	int		dir;
	t_dvect	door_left_edge;
	t_dvect	door_right_edge;
	int		isopen;
	double	open_time;
}	t_sprite;

/*
	@param *line - line read by the parser, put here to easily free everything
	@param fd - same as above, it is the file descriptor created to read
	@param n_h and n_d - number of holes and doors
*/
typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*tex[6];
	t_assets		*assets;
	char			**map;
	mlx_image_t		*minimap;
	size_t			n_rows;
	size_t			n_col;
	t_player		*p;
	char			*line;
	int				fd;
	double			dist_arr[WIN_W];	// ???
	int				dir_arr[WIN_W];		// ???
	t_sprite		*sprite;
	int				n_total_sprites;
	int				n_h;
	int				n_d;
}	t_cub3d;

/*
	*** Variables related to raycasting calculation ***
	@param raydir - ray direction
	@param ray_len - distance from the current position to next x/y side
	@param ray_delta - length from one x/y side to the next
	@param wall_dist - distance from the player to the wall
	@param hit - 0 if the ray didn't hit a wall
	@param wall_dir - NORTH_SOUTH or WEST_EAST
	@param line_h - visible wall height for pixel_x
*/
typedef struct s_raycast
{
	t_dvect	raydir;
	t_dvect	ray_len;
	t_dvect	ray_delta;
	double	wall_dist;
	double	door_dist;
	int		door_dir;
	double	wall_x;
	int		hit;
	int		wall_dir;
	int		line_h;
	int		tex_x;
	int		line_start;
	int		line_end;
	int		b_size;
	char	d;

	t_ivect	ray;
}	t_raycast;

/*
	Sprites are rendered separately, whitesp inside map are considered sprites.
	@param transform - transformed coordinates
	@param h - sprite height for current distance
	@param w - sprite width
	@param uncut_x - location of sprite's start
*/
typedef struct s_spritecast
{
	t_dvect		transform;
	int			left_x; // draw start ???
	int			right_x;
	int			up_right; //draw end ???
	int			up_left;
	int			lo_left; //draw start ???
	int			lo_right; //draw end ???
	t_ivect		start; //draw start
	t_ivect		end; //draw end
	int			h;
	int			w;
	int			uncut_x;
	t_dvect		transform2;
	int			w2;
	int			h2;
	int			isdoor;
}	t_spritecast;

typedef struct s_ftile
{
	double	dist;
	double	delta;
	int		bottom;
	int		h;
}	t_ftile;

#endif
