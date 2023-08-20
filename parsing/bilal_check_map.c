/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:51:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 17:16:34 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_main.h"

int	check_chars(char *map)
{
	int	i;
	int	j;
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
		ft_error("Error\nMap Error", map, NULL);
	if (check_chars(map))
		ft_error("Error\nMap Error", map, NULL);
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
