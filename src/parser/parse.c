/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:38:12 by ncasteln          #+#    #+#             */
/*   Updated: 2024/01/17 17:12:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	parse_player(data);
	path_validation(data);
	/*
	DECISIONS:
		- map_ass_same_line.cub (means: the map starts in the same line of an asset) is considered invalid
		- map_texture_dir.cub (means: an asset file name is a directory like ./path/) is invalid
		- ass_04.cub (means: color value has positive sign) is valid
		- ass_05.cub (means: color value == 0 and has positive sign) is valid
		- ass_06.cub (means: color value like 0000233 is 233) is valid
	- textures has .xpm extension ??
	*/
}
