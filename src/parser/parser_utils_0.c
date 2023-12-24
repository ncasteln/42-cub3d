/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:48:00 by nico              #+#    #+#             */
/*   Updated: 2023/12/24 10:30:56 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump_whitspaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

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
