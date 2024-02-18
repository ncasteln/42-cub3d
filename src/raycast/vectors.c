/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubina <mrubina@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:01:50 by mrubina           #+#    #+#             */
/*   Updated: 2024/02/19 00:45:58 by mrubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
given the magnitude and the direction of the vector
the vector is calculated
input: direction, magnitude
output: corresponding vector
 */
void	get_vector(t_dvect *vector, t_dvect *dir, double magnitude)
{
	double	cos;
	double	sin;
	double	tan;

	tan = dir->y / dir->x;
	cos = sign(dir->x) * sqrtf(1/(powf(tan, 2) + 1));
	sin = sign(dir->y) * sqrtf(1 - powf(cos, 2));
	set_vect(vector, magnitude * cos, magnitude * sin);
}

/*
given x and the direction we get y or the other way round
dim is the dimention that we have to calculate
 */
void	get_second_dim(t_dvect *vector, t_dvect *dir, int dim)
{
	double	tan;

	if (dir->x != 0)
	{
		tan = dir->y / dir->x;
		if (dim == Y)
			vector->y = tan * vector->x;
		else if (dim == X && tan != 0)
			vector->x = vector->y / tan;
	}
	else if (dim == X)
		vector->x = 0.0;
}

//rotates any vector by a given angle (radians)
void	rotate_vector(t_dvect *v, double angle)
{
	double temp_x;

	temp_x = v->x;
	v->x = v->x * cosf(angle) - v->y * sinf(angle);
	v->y = temp_x * sinf(angle) + v->y * cosf(angle);
}
