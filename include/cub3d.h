/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:53 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/22 20:35:44 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "math.h"
# include "defs.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>



//functions
void	key_hook(mlx_key_data_t keydata, void *param);
void	mouse_hook(mlx_key_data_t keydata, int x, int y, void *param);
void	win_close(mlx_t* mlx);
void rayCasting(t_data *data);
void vert_line(t_data *data, int x, int drawStart, int drawEnd, int color);
void refresh(void *param);
void clearScreen(t_data *data);
void rotateP(t_data *data, double angle);
#endif