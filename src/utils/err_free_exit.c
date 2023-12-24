/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_free_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:22:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/24 12:06:11 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_err_msg(int err_n)
{
	if (err_n == E_ARGC)
		return ("invalid argc");
	if (err_n == E_INV_EXT)
		return ("invalid file extension");
	if (err_n == E_PARSE_ASSETS)
		return ("invalid assets");
	if (err_n == E_DUP_ASSET)
		return ("duplicate asset");
	if (err_n == E_INV_ASSET)
		return ("invalid asset");
	if (err_n == E_MISS_ASSET)
		return ("missing asset");
	return ("unknow error");
}

static void	error(char *func_name, int err_n)
{
	char	*err_msg;

	if (err_n <= 106)
		err_msg = strerror(err_n);
	else
		err_msg = get_err_msg(err_n);
	ft_putendl_fd("Error", 2);
	if (func_name)
	{
		ft_putstr_fd(func_name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg, 2);
}

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
	if (assets->f)
		free(assets->f);
	if (assets->c)
		free(assets->c);
	free(assets);
}

static void	free_dptr(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static void	free_data(t_cub3d *data)
{
	if (data->assets)
		free_assets(data->assets);
	if (data->line)
		free(data->line);
	if (data->map)
		free_dptr(data->map);
}

void	err_free_exit(char *s, t_cub3d *data, int err_n)
{
	if (err_n)
		error(s, err_n);
	free_data(data);
	exit (err_n);
}
