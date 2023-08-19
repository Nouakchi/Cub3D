/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:51:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 11:10:19 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_map_01snew.h"

int	ft_strlen_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_strlen_width(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

int	check_chars(char **map)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				c++;
			if (c > 1)
				return (1);
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'S'
				&& map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (1);
		}
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
			if (j == 0 && map[i][j] != '\0')
				return (1);
			if (i == 0 || i == ft_strlen_height(map) - 1 || j == 0
				|| j == ft_strlen_width(map) - 1)
			{
				if (map[i][j] != ' ' && map[i][j] != '1')
					return (1);
			}
			if (map[i][j] != ' ' && map[i][j] != '1')
			{
				if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i
					+ 1][j] == ' ' || map[i - 1][j] == ' ' || map[i][j
					+ 1] == '\0' || map[i][j - 1] == '\0' || map[i
					+ 1][j] == '\0' || map[i - 1][j] == '\0')
					return (1);
			}
		}
	}
	return (0);
}

int	check_map(char **map)
{
	if (ft_strlen_height(map) < 3 || ft_strlen_width(map) < 3)
		return (1);
	if (check_chars(map))
		return (free_map(map), 1);
	if (check_walls(map))
		return (free_map(map), 1);
	// Except for the map content,
	//	each type of element can be separated by one or more empty line(s).
	// if (check_empty_lines(map))
	// 	return (free_map(map), 1);
	// // Except for the map content which always has to be the last,
	//	each type of element can be set in any order in the file.
	// if (check_order(map))
	// 	return (free_map(map), 1);
	// // Except for the map,
	//	each type of information from an element can be separated by one or more space(s).
	// if (check_spaces(map))
	// 	return (free_map(map), 1);
	return (0);
}




char	**add_spaces(char **map)
{
	
}
