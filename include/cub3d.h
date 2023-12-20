/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:57:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/20 12:27:30 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "errno.h"
#include <string.h>
#include <fcntl.h>

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
// #include "MLX42.h"

enum err
{
	CE_ARGC = 107,
	CE_PARSEASSETS,
	CE_DUPASS,
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

typedef struct s_cub3d
{
	t_assets	*assets;
	char		*map;
}	t_cub3d;


int		parse(int argc, char **argv, t_cub3d *data);
void	parse_assets(char *f_name, t_cub3d *data);

void	err_free_exit(char *func_name, t_cub3d *data, int err_n);

#endif
