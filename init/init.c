/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 05:32:35 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:49:41 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	data_map_init(t_data *data)
{
	data->map_data.map_elements.east_text = NULL;
	data->map_data.map_elements.west_text = NULL;
	data->map_data.map_elements.north_text = NULL;
	data->map_data.map_elements.south_text = NULL;
	data->map_data.map_elements.colors_east = NULL;
	data->map_data.map_elements.colors_west = NULL;
	data->map_data.map_elements.colors_north = NULL;
	data->map_data.map_elements.colors_south = NULL;
	data->map_data.map = NULL;
	data->img_north.img = NULL;
	data->img_south.img = NULL;
	data->img_east.img = NULL;
	data->img_west.img = NULL;
	data->map_data.map_elements.frgb.r = -1;
	data->map_data.map_elements.crgb.r = -1;
}

void	init_player_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->map_data.map_width = 0;
	while (data->map_data.map[++i])
	{
		j = -1;
		while (data->map_data.map[i][++j])
		{
			if (ft_strchr("NWSE", data->map_data.map[i][j]))
			{
				data->player.y_pos = i * 64 + 32;
				data->player.x_pos = j * 64 + 32;
				data->player.start_angle = data->map_data.map[i][j];
				data->map_data.map[i][j] = '0';
			}
		}
		if (data->map_data.map_width < (int)ft_strlen(data->map_data.map[i]))
			data->map_data.map_width = (int)ft_strlen(data->map_data.map[i]);
	}
	data->map_data.map_height = i;
}

void	init_angles_moves(t_data *data)
{
	if (data->player.start_angle == 'N')
		data->ray.angle = 120;
	else if (data->player.start_angle == 'W')
		data->ray.angle = 210;
	else if (data->player.start_angle == 'S')
		data->ray.angle = 300;
	else
		data->ray.angle = 30;
	data->player.view_angle = data->ray.angle - 30;
	data->moves.move_r = 0;
	data->moves.move_l = 0;
	data->moves.move_f = 0;
	data->moves.move_b = 0;
}

int	free_all_success(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}
