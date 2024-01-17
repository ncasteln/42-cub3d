/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:57:46 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/17 10:44:50 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "errno.h"
#include <string.h>
#include <fcntl.h>
#include <math.h>

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "MLX42.h"

#include "typedef.h"
#include "cub3d_bonus.h"

#ifndef BONUS
# define BONUS 0
#endif

// -------------------------------------------------------------------- PARSING
void	parse(int argc, char **argv, t_cub3d *data);
void	parse_file_content(char *f_name, t_cub3d *data);
void	parse_type_id(char **line, char *type_id, t_cub3d *data);
char	*extract_type_id_value(char **line, char *id, t_cub3d *data);

void	parse_player(t_cub3d *data);
void	path_validation(t_cub3d *data);

// -------------------------------------------------------------- PARSING UTILS
int			is_texture(char *line);
void		jump_whitspaces(char **line);
int			is_duplicate_asset(char *id, t_cub3d *data);
int			is_missing_asset(t_assets *assets);

void		store_map_line(char *line, t_cub3d *data);
int			is_valid_map_line(char *s);
int			is_valid_map_char(char c);
uint32_t	str_to_ul(char *s);

// ---------------------------------------------------------------------- UTILS
void	err_free_exit(char *s, t_cub3d *data, int err_n);
void	free_data(t_cub3d *data);
void	free_dptr(char **p);
int		is_empty_line(char *s);

// ---------------------------------------------------------------- PRINT UTILS
void	print_map(char **p, int	row_len);
void	print_assets(t_assets *assets);

// ----------------------------------------------------------------- RAYCASTING
void	key_hook(mlx_key_data_t keydata, void *param);
void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param);
void	win_close(mlx_t* mlx);
void	raycasting(t_cub3d *data);
//void	vert_line(t_cub3d *data, int x, int draw_start, int draw_end, int color);
void vert_line(t_cub3d *data, int x, int draw_start, int draw_end);
void	refresh(void *param);
void	clearScreen(t_cub3d *data);
void	rotateP(t_move *data, double angle);
uint32_t dim(uint32_t color, uint32_t shift);
//void move(t_cub3d *data, double move);
void move(t_cub3d *data, double move, int dir);
void rotateV(double *x, double *y, double angle);
int check_space(t_cub3d *data, double delta_x, double delta_y);
int sign(double x);
void move_s(t_cub3d *data, double move, int dir);
t_dvect *set_vect(t_dvect *v, double x, double y);
void draw_square(t_cub3d *data, int xStart, int yStart, int side, int color);
uint32_t getpixcol(uint8_t *p);
uint32_t getcol(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void load_textures(t_cub3d *data);
#endif
