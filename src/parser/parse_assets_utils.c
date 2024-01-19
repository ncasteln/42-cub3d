/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:48:00 by nico              #+#    #+#             */
/*   Updated: 2024/01/19 11:41:00 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*is_valid_asset_id(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') // || line[i] == '\n' added
		i++;
	if (!ft_strncmp(line + i, "NO", 2))
		return ("NO");
	if (!ft_strncmp(line + i, "EA", 2))
		return ("EA");
	if (!ft_strncmp(line + i, "SO", 2))
		return ("SO");
	if (!ft_strncmp(line + i, "WE", 2))
		return ("WE");
	if (!ft_strncmp(line + i, "F", 1))
		return ("F");
	if (!ft_strncmp(line + i, "C", 1))
		return ("C");
	if (BONUS && !ft_strncmp(line + i, "DO", 2))
		return ("DO");
	return (NULL);
}

int	is_texture(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2))
		return (1);
	if (!ft_strncmp(line, "SO", 2))
		return (1);
	if (!ft_strncmp(line, "WE", 2))
		return (1);
	if (BONUS && !ft_strncmp(line, "DO", 2))
		return (1);
	return (0);
}

int	is_duplicate_asset(char *id, t_cub3d *data)
{
	if (!ft_strncmp(id, "NO", 2))
		if (data->assets->no)
			err_free_exit("NO", data, E_DUP_ASSET);
	if (!ft_strncmp(id, "EA", 2))
		if (data->assets->ea)
			err_free_exit("EA", data, E_DUP_ASSET);
	if (!ft_strncmp(id, "SO", 2))
		if (data->assets->so)
			err_free_exit("SO", data, E_DUP_ASSET);
	if (!ft_strncmp(id, "WE", 2))
		if (data->assets->we)
			err_free_exit("WE", data, E_DUP_ASSET);
	if (!ft_strncmp(id, "F", 1))
		if (data->assets->f)
			err_free_exit("F", data, E_DUP_ASSET);
	if (!ft_strncmp(id, "C", 1))
		if (data->assets->c)
			err_free_exit("C", data, E_DUP_ASSET);
	return (0);
}

/*
	Doors are not required to run the game, they are just optional and the
	game can still run without them.
*/
int	is_missing_asset(t_assets *assets)
{
	if (!assets->no)
		return (1);
	if (!assets->ea)
		return (1);
	if (!assets->so)
		return (1);
	if (!assets->we)
		return (1);
	if (!assets->f)
		return (1);
	if (!assets->c)
		return (1);
	return (0);
}
