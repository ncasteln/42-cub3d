/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/01/18 16:09:53 by ncasteln         ###   ########.fr       */
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
	char		*d;
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

//variables related to movement
typedef struct	s_move {

	t_dvect			pos; // character position
	t_dvect			dir; // look direction
	t_dvect			plane; //camera plane
	t_ivect		map;	//square coordinates - left upper side of the sqare
	mlx_texture_t *tex[4];
}	t_move;


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
	t_move	*mv;
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
	t_dvect	side_dist;
	t_dvect	delta_dist;
	double	wall_dist;
	double	wall_x;
	int		hit; //0 if the ray didn't hit a wall
	int		side;
	int		line_h; //visible wall height for pixel_x
	int		tex_x;
	int		line_start;
	int		line_end;
}	t_raycast;

#endif
