/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:38:12 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/26 11:45:23 by nico             ###   ########.fr       */
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
	print_map(data->map);
	/*
		TO DO FOR MAP
		flood fill()
	
		needed ???
			- player on the edge
			- holes?
	*/
	/*
		FIXES FOR ASSETS
		needed ???
			- check if open() a directory for textures
			- textures has .xpm extension ??
	*/
}
