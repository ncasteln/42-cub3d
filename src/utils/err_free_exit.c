/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_free_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:22:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/20 19:15:37 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_err_msg(int err_n)
{
	if (err_n == E_ARGC)
		return ("invalid argc");
	if (err_n == E_PARSE_ASSETS)
		return ("invalid assets");
	if (err_n == E_DUP_ASSET)
		return ("duplicate asset");
	if (err_n == E_INV_ASSET)
		return ("invalid asset");
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

void	err_free_exit(char *func_name, t_cub3d *data, int err_n)
{
	if (err_n)
		error(func_name, err_n);
	// free everything
	exit (err_n);
}
