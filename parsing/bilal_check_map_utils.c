/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_check_map_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:57:36 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 17:03:51 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_main.h"

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

int	check_chars_utils(char map)
{
	if (map != '1' && map != '0' && map != 'S' && map != 'N' && map != 'E'
		&& map != 'W' && map != ' ' && map != '\n')
		return (1);
	return (0);
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
