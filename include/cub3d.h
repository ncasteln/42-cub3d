/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:57:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/26 17:30:04 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "errno.h"
#include <string.h>
#include <fcntl.h>
#include <math.h>

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
// #include "MLX42.h"

#include "typedef.h"

// -------------------------------------------------------------------- PARSING
void	parse(int argc, char **argv, t_cub3d *data);
void	parse_file_content(char *f_name, t_cub3d *data);
void	parse_type_id(char **line, char *type_id, t_cub3d *data);
char	*extract_type_id_value(char **line, char *id, t_cub3d *data);

void	parse_player(t_cub3d *data);
void	path_validation(t_cub3d *data);

// -------------------------------------------------------------- PARSING UTILS
int		is_texture(char *line);
void	jump_whitspaces(char **line);
int		is_duplicate_asset(char *id, t_cub3d *data);
int		is_missing_asset(t_assets *assets);

void	store_map_line(char *line, t_cub3d *data);
int		is_valid_map_line(char *s);
int		is_valid_map_char(char c);

// ---------------------------------------------------------------------- UTILS
void	err_free_exit(char *s, t_cub3d *data, int err_n);
void	free_data(t_cub3d *data);
void	free_dptr(char **p);

// -----------------------------------------------------------------PRINT UTILS
void	print_map(char **p, int	row_len);
void	print_assets(t_assets *assets);

#endif
