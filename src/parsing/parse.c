/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:38:12 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/18 14:34:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Parses:
	0) .cub extension

	1) Map content
		- Surrounded by walls
		- No empty lines
		- Always the last
		- Char allowed: 0 1 N E S W (only one letter)
		- Decide if handle spaces or not

	2) Textures - NO   SO   WE   EA   F   C
		- Random number of empty lines between
		- Allowed:
			- NO WE SO EA + path
			- F C + rgb color
		- Any order

	"Error\n" + custom message
*/

int	parse(int argc, char **argv)
{
	if (argc != 2)
		return (error(CE_ARGC), 1);

	return (0);
}
