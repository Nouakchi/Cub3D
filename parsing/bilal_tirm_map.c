/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_tirm_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 09:28:29 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/21 14:05:16 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	start_spaces(char **map)
{
	int	i;
	int	j;
	int	count;
	int	min;

	i = 0;
	min = ft_strlen_width(map);
	while (map[i])
	{
		j = 0;
		count = 0;
		while (map[i][j] && map[i][j] == ' ')
		{
			count++;
			j++;
		}
		if (count < min)
			min = count;
		i++;
	}
	return (min);
}

void	end_spaces(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map_data.map[++i])
	{
		j = ft_strlen(data->map_data.map[i]) - 1;
		while (j >= 0 && data->map_data.map[i][j] == ' ')
		{
			data->map_data.map[i][j] = '\0';
			j--;
		}
	}
}

void	trim_map(t_data *data)
{
	int	start;
	int	i;
	int	j;

	end_spaces(data);
	start = start_spaces(data->map_data.map);
	i = -1;
	while (data->map_data.map[++i])
	{
		j = 0;
		while (data->map_data.map[i][j] && data->map_data.map[i][j + start])
		{
			data->map_data.map[i][j] = data->map_data.map[i][j + start];
			j++;
		}
		data->map_data.map[i][j] = '\0';
	}
}
