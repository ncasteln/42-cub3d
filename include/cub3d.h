/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:57:46 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/21 08:15:18 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "errno.h"
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/* CUSTOM HEADERS */
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "MLX42.h"
# include "typedef.h"

// -------------------------------------------------------------------- PARSING
void	parse(int argc, char **argv, t_cub3d *data);
void	parse_file_content(char *f_name, t_cub3d *data);
void	parse_player(t_cub3d *data);
void	path_validation(t_cub3d *data);

// ------------------------------------------------------- ASSETS PARSING UTILS
void	parse_assets(char **line, char *type_id, t_cub3d *data);
char	*extract_asset_value(char **line, char *id, t_cub3d *data);
int		is_valid_color(char *color);
char	*rgb_to_hex_string(char *color);
char	*is_valid_asset_id(char *line);
int		is_texture(char *line);
int		is_duplicate_asset(char *id, t_cub3d *data);
int		is_missing_asset(t_assets *assets);
void	check_valid_doors(t_cub3d *data);

// ---------------------------------------------------------- MAP PARSING UTILS
void	jump_whitespaces(char **line);
void	store_map_line(char *line, t_cub3d *data);
int		is_valid_map_line(char *s);

// ------------------------------------------------------------ PATH VALIDATION
char	**rectangolize(t_cub3d *data);
int		get_n_rows(char **map);
void	flood_fill(int py, int px, char **map_cpy, t_cub3d *data);
void	trim_empty_lines(t_cub3d *data);

// ---------------------------------------------------------------------- UTILS
void	init_cub3d(t_cub3d *data);
void	init_move(t_player *p);
void	err_free_exit(char *s, t_cub3d *data, int free_mlx, int err_n);
void	free_data(t_cub3d *data);
void	free_dptr(char **p);
int		is_blank_line(char *s);
void	count_sprites(t_cub3d *data);

// ---------------------------------------------------------------- PRINT UTILS
void	print_map(char **p, int	row_len);
void	print_assets(t_assets *assets);

// ----------------------------------------------------------------- RAYCASTING
void	key_hook(mlx_key_data_t keydata, void *param);
void	raycasting(t_cub3d *data);
void	refresh(void *param);
void rotate_player(t_player *p, double angle);
void move(t_cub3d *data, double move, int dir);
void rotate_vector(t_dvect *v, double angle);
int sign(double x);
t_dvect *set_vect(t_dvect *v, double x, double y);
void	get_vector(t_dvect *vector, t_dvect *dir, double magnitude);
void	get_second_dim(t_dvect *vector, t_dvect *dir, int dim);
uint32_t readcol(uint8_t *p);
uint32_t getcol(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void load_textures(t_cub3d *data);
void correction(t_cub3d *data);
int select_texture(t_raycast *rc);
char read_map(t_cub3d *data, size_t y, size_t x);
void	refine(t_cub3d *data, t_dvect *incr);
void	set_draw_wall(t_raycast *rc);
void	putline(t_cub3d *data, int x, mlx_texture_t	*tex, t_raycast *rc);

// ------------------------------------------------------------ SPRITES CASTING
void	sprites(t_cub3d *data);
void	bubble(t_sprite *sprite, int n);
void	set_dist(t_cub3d *data);
double sprite_dist_sq(t_sprite s, t_dvect p);
void put_sprites(t_cub3d *data);
void	draw_door(t_cub3d *data, t_spritecast *sc, mlx_texture_t *tex, int i);
void	set_draw_door(t_spritecast *sc);
void set_door(int n, int y, int x, t_cub3d *data);
void	create_sprite_list(t_cub3d *data);
void	set_sprite(int n, int y, int x, t_cub3d *data);
int	door_open(t_cub3d *data, int x, int y);

// -------------------------------------------------------------------- MINIMAP
// void	check_behind_doors(t_cub3d *data, char **map_cpy); // mnot needed
void	minimap(t_cub3d *data);

#endif
