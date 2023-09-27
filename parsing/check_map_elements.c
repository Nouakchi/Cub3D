/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:06:15 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 04:09:45 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	parse_colors(char *identifier, char *path_rgb, t_data *data)
{
	if (!ft_strcmp(identifier, "F")
		&& data->map_data.map_elements.frgb.r == -1)
	{
		if (!parse_rgb(path_rgb, &data->map_data.map_elements.frgb))
			return (0);
	}
	else if (!ft_strcmp(identifier, "C")
		&& data->map_data.map_elements.crgb.r == -1)
	{
		if (!parse_rgb(path_rgb, &data->map_data.map_elements.crgb))
			return (0);
	}
	else
		return (0);
	return (1);
}

static int	parse_textures(char *identifier, char *path_rgb, t_data *data)
{
	int		path_fd;

	path_fd = open(path_rgb, O_RDONLY);
	if (path_fd == -1) // ADD BY BILAL
		return (0);
	close(path_fd);
	if (!ft_strcmp(identifier, "NO")
		&& !data->map_data.map_elements.north_text)
		data->map_data.map_elements.north_text = ft_strdup(path_rgb);
	else if (!ft_strcmp(identifier, "SO")
		&& !data->map_data.map_elements.south_text)
		data->map_data.map_elements.south_text = ft_strdup(path_rgb);
	else if (!ft_strcmp(identifier, "WE")
		&& !data->map_data.map_elements.west_text)
		data->map_data.map_elements.west_text = ft_strdup(path_rgb);
	else if (!ft_strcmp(identifier, "EA")
		&& !data->map_data.map_elements.east_text)
		data->map_data.map_elements.east_text = ft_strdup(path_rgb);
	else
		return (0);
	return (1);
}

int	parse_element(char *identifier, char *path_rgb, t_data *data, int *all_in)
{
	if (ft_strlen(identifier) == 1)
	{
		if (!parse_colors(identifier, path_rgb, data))
			return (0);
	}
	else
		if (!parse_textures(identifier, path_rgb, data))
			return (0);
	*all_in = *all_in + 1;
	return (1);
}

static int	parse_line(char **key, char **value, char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ')
		;
	if (!line[i])
		return (0);
	*key = &line[i];
	*value = ft_strchr(&line[i], ' ');
	if (!*value)
		return (0);
	*((*value)++) = '\0';
	if (!*value)
		return (0);
	while (**value == ' ')
		(*value)++;
	if (!*(*value + 1))
		return (0);
	return (1);
}

int	check_element(int map, t_data *data)
{
	int		all_in;
	char	*line;
	char	*key;
	char	*value;

	all_in = 0;
	line = NULL;
	key = NULL;
	value = NULL;
	while (all_in < 6)
	{
		if (!read_line(map, &line))
			return (free(line), 0);
		if (!ft_strcmp(line, ""))
			continue ;
		if (!parse_line(&key, &value, line))
			return (free(line), 0);
		if (ft_strlen(key) > 2 || !parse_element(key, value, data, &all_in))
			return (free(line), 0);
	}
	return (free(line), 1);
}
