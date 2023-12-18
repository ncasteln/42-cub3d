/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:53 by mrubina           #+#    #+#             */
/*   Updated: 2023/12/18 18:43:45 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

//constants
# define WIN_W 1200
# define WIN_H 1200

//structures

typedef struct s_data {
	mlx_t* mlx;
	mlx_image_t* img;
}	t_data;

#endif