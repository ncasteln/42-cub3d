/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:01:30 by nico              #+#    #+#             */
/*   Updated: 2024/01/04 16:20:05 by ncasteln         ###   ########.fr       */
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
