/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:38:12 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/20 10:21:19 by nico             ###   ########.fr       */
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

int	parse(int argc, char **argv, t_cub3d *data)
{

	if (argc != 2)
		err_free_exit("parse", data, CE_ARGC);
	// parse extension
	parse_assets(argv[1], data);
	// if something wrong exits
	// parse_map()

	return (0);
}
