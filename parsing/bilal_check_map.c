/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:51:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/20 09:00:59 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int     check_map_pars(int map_fd, t_data *data)
{
	char   *init_map;

	init_map = get_init_map(map_fd);
	init_map = ft_strtrim(init_map, "\n");
	if (check_init_map(init_map))
		ft_error("Map Error", init_map, NULL);
	data->map_data.map = ft_split(init_map, '\n');
	if (!data->map_data.map)
		ft_error("Malloc Error", init_map, NULL);
	free(init_map);
	if (check_map(data->map_data.map))
		ft_error("Map Error", NULL, NULL);
	return (0);
}

int	check_chars(char *map)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (map[++i])
	{
		if (map[i] == 'S' || map[i] == 'N' || map[i] == 'E' || map[i] == 'W')
			c++;
		if (c > 1)
			return (1);
		if (check_chars_utils(map[i]))
			return (1);
	}
	if (c == 0)
		return (1);
	return (0);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (i == 0 || i == ft_strlen_height(map) - 1 || j == 0
				|| j == ft_strlen_width(map) - 1)
			{
				if (map[i][j] != ' ' && map[i][j] != '1')
					return (1);
			}
			if (map[i][j] != ' ' && map[i][j] != '1')
			{
				if (check_walls_utils(map, i, j))
					return (1);
			}
		}
	}
	return (0);
}

int	check_newline(char *map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (1);
	}
	return (0);
}

int	check_init_map(char *map)
{
	if (check_newline(map))
		ft_error("Map Error", map, NULL);
	if (check_chars(map))
		ft_error("Map Error", map, NULL);
	return (0);
}

int	check_map(char **map)
{
	if (ft_strlen_height(map) < 3 || ft_strlen_width(map) < 3)
		return (free_map(map), 1);
	if (check_walls(map))
		return (free_map(map), 1);
	return (0);
}
