/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:48:00 by nico              #+#    #+#             */
/*   Updated: 2023/12/23 12:57:15 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_texture(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2))
		return (1);
	if (!ft_strncmp(line, "SO", 2))
		return (1);
	if (!ft_strncmp(line, "WE", 2))
		return (1);
	return (0);
}

int is_color(char *line)
{
	if (!ft_strncmp(line, "F", 1))
		return (1);
	if (!ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

int is_duplicate_asset(char *id, t_cub3d *data)
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

int	are_assets_complete(t_assets *assets)
{
	if (!assets->no)
		return (0);
	if (!assets->ea)
		return (0);
	if (!assets->so)
		return (0);
	if (!assets->we)
		return (0);
	if (!assets->f)
		return (0);
	if (!assets->c)
		return (0);
	return (1);
}

int	store_texture_path(char *line, t_cub3d *data)
{
	char	*path;

	path = ft_strdup(line + 2);
	if (!path)
		return (1);
	if (!ft_strncmp(line, "NO", 2))
		data->assets->no = path;
	if (!ft_strncmp(line, "EA", 2))
		data->assets->ea = path;
	if (!ft_strncmp(line, "SO", 2))
		data->assets->so = path;
	if (!ft_strncmp(line, "WE", 2))
		data->assets->we = path;
	return (0);
}

int	store_color(char *line, t_cub3d *data)
{
	char	*color;

	color = ft_strdup(line + 1);
	if (!color)
		return (1);
	if (!ft_strncmp(line, "F", 1))
		data->assets->f = color;
	if (!ft_strncmp(line, "C", 1))
		data->assets->c = color;
	return (0);
}
