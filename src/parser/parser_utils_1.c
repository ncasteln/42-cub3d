/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:51:33 by nico              #+#    #+#             */
/*   Updated: 2023/12/25 19:17:35 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_valid_map_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && is_valid_map_char(s[i]))
		i++;
	if (i == ft_strlen(s) - 1) // because of the new line
		return (1);
	return (0);
}

int	is_blank_string(char *s) // check if needed
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

