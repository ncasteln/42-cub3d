/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:38:12 by ncasteln          #+#    #+#             */
/*   Updated: 2024/02/23 08:37:27 by ncasteln         ###   ########.fr       */
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
		err_free_exit("parse", data, 0, E_ARGC);
	if (!is_valid_extension(argv[1], ".cub"))
		err_free_exit("parse", data, 0, E_INV_EXT);
	parse_file_content(argv[1], data);
	parse_player(data);
	path_validation(data);
	if (BONUS)
	{
		check_valid_doors(data);
		if (data->n_col > 35 || data->n_rows > 35)
			data->minimap_pixel = 5;
	}
}
