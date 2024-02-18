/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:49:00 by nico              #+#    #+#             */
/*   Updated: 2024/02/15 11:21:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_assets(t_assets *assets)
{
	if (assets->no)
		free(assets->no);
	if (assets->ea)
		free(assets->ea);
	if (assets->so)
		free(assets->so);
	if (assets->we)
		free(assets->we);
	if (BONUS && assets->d)
		free(assets->d);
	free(assets);
}

void	free_dptr(char **p)
{
	int	i;

	i = 0;
	if (p)
	{
		while (p[i])
		{
			free(p[i]);
			i++;
		}
		free(p);
	}
}

void	free_data(t_cub3d *data)
{
	if (data->assets)
		free_assets(data->assets);
	if (data->line)
		free(data->line);
	if (data->map)
		free_dptr(data->map);
	if (data->p)
		free(data->p);
	if (data->fd != -1)
		close(data->fd);
}
