/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:57:36 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/27 01:18:31 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	int	j;
	int	count;
	int	max;

	i = -1;
	max = 0;
	while (map[++i])
	{
		count = 0;
		j = -1;
		while (map[i][++j])
			count++;
		if (count > max)
			max = count;
	}
	return (max);
}

int	check_walls_utils(char **map, int i, int j)
{
	if (map[i][j] != ' ' && map[i][j] != '1')
	{
		if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' '
			|| map[i - 1][j] == ' ' || map[i][j + 1] == '\0' || map[i][j
			- 1] == '\0' || map[i + 1][j] == '\0' || map[i - 1][j] == '\0')
			return (1);
	}
	return (0);
}

int	check_init_map(char *map)
{
	if (check_newline(map))
		return (1);
	if (check_chars(map))
		return (1);
	return (0);
}

int	check_map(char **map)
{
	if (ft_strlen_height(map) < 3 || ft_strlen_width(map) < 3)
		return (1);
	if (check_walls(map))
		return (1);
	return (0);
}
