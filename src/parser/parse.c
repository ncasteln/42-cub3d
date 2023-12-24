/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:38:12 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/24 19:51:45 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Parses:
	[OK] 0) .cub extension

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

static int	is_valid_extension(const char *s, const char *ext)
{
	int	i;

	if (!s || !ext)
		return (0);
	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == '.')
		{
			if (!(ft_strncmp(s + i, ext, ft_strlen(ext))))
				return (1);
		}
		i--;
	}
	return (0);
}

void	parse(int argc, char **argv, t_cub3d *data)
{
	if (argc != 2)
		err_free_exit("parse", data, E_ARGC);
	if (!is_valid_extension(argv[1], ".cub"))
		err_free_exit("parse", data, E_INV_EXT);
	parse_file_content(argv[1], data);
	print_map(data->map);
	// flood fill()
}
