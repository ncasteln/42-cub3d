/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/02/07 18:33:22 by ncasteln         ###   ########.fr       */
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

// ------------------------------------------------------------------- TEXTURES
# define NO 0
# define WE 1
# define SO 2
# define EA 3
# define H 4	// hole
# define D 5	// door
# define S 6	// sprite

# define RED		0x990000FF
# define GREEN		0x00FF00FF
# define BLUE		0x0000FF77
# define ORANGE		0xDD7700FF
# define WHITE		0xFFFFFFFF
# define WALLC WHITE

# define FORWARD	100
# define BACK		200
# define RIGHT		300
# define LEFT		400

// --------------------------------------------------------------------- ERRORS
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

// -------------------------------------------------------------------- STRUCTS
typedef struct s_assets
{
	char		*no;
	char		*ea;
	char		*so;
	char		*we;
	uint32_t	f;
	uint32_t	c;
	char		*d;		// door is actually a sprite
	char		*s;		// $ sprite
	char		*h;	// hole
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

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	dist;
	char	c;		// D S or H
}	t_sprite;

typedef struct s_cub3d
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	mlx_image_t*	img1;
	mlx_texture_t	*tex[7];	// modify to dynamic allocation to differentiate with bonus ???
	t_assets		*assets;
	char			**map;
	mlx_image_t		*minimap;
	size_t			n_rows;
	size_t			n_col;
	t_player		*p;
	char			*line;
	int				fd;

	t_sprite		*sprite;
	int				n_h;	// number of holes
	int				n_d;	// number of doors
	int				n_s;	// number of sprites
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
