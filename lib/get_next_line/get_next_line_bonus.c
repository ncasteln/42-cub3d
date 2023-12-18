/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:47:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/05 14:38:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	get_substr_len(char *s, int start)
{
	int	i;

	i = 0;
	if (!start)
	{
		while (s[i] && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	else
	{
		while (s[start])
		{
			start++;
			i++;
		}
	}
	return (i);
}

static char	*split(char **store)
{
	char	*left;
	char	*temp;
	int		left_len;
	int		right_len;

	temp = NULL;
	left_len = get_substr_len(*store, 0);
	left = ft_substr_mod(*store, 0, left_len);
	right_len = get_substr_len(*store, left_len);
	if (right_len == 0)
	{
		free(*store);
		*store = NULL;
	}
	else
	{
		temp = *store;
		*store = ft_substr_mod(*store, left_len, right_len);
		free(temp);
	}
	return (left);
}

static char	*init_buffer(char **buff, int fd)
{
	if (fd >= 0)
	{
		if (BUFFER_SIZE > 0)
		{
			*buff = malloc ((BUFFER_SIZE + 1) * sizeof(char));
			if (!*buff)
				return (NULL);
			return (*buff);
		}
	}
	return (NULL);
}

static char	*stop_to_read(char **line, char *buff, int n_read)
{
	if (*line)
	{
		if (n_read == -1)
			return (free(buff), free(*line), *line = NULL, NULL);
		if (n_read == 0)
			return (free(buff), split(line));
	}
	return (free(buff), NULL);
}

char	*get_next_line(int fd)
{
	static char	*line[FOPEN_MAX];
	char		*buff;
	int			n_read;

	buff = init_buffer(&buff, fd);
	if (!buff)
		return (NULL);
	n_read = 0;
	while (!(ft_strchr_mod(line[fd], '\n')))
	{
		n_read = read(fd, buff, BUFFER_SIZE);
		if (n_read == -1)
			return (stop_to_read(&line[fd], buff, n_read));
		buff[n_read] = '\0';
		if (n_read == 0)
			return (stop_to_read(&line[fd], buff, n_read));
		if (n_read > 0)
		{
			line[fd] = ft_strjoin_mod(line[fd], buff);
			if (!line[fd])
				return (free(buff), NULL);
		}
	}
	return (free(buff), split(&line[fd]));
}
