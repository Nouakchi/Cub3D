/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:59:16 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:44:37 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	mouse_visibility(t_data *data)
{
	data->mouse_app = 0;
	if (mlx_mouse_hide() == -1)
		return (1);
	return (0);
}

static void	draw_mini_cube(t_data *data, int x, int y, unsigned int color)
{
	int	i;
	int	j;

	i = x - 6;
	while (++i < x + 6)
	{
		j = y - 6;
		while (++j < y + 6)
			my_mlx_pixel_put(&data->img, j, i, color);
	}
}

static void	put_the_mini_map(t_data *data, t_mini_map mm)
{
	if (mm.i < data->map_data.map_height && mm.i >= 0 && \
		mm.j < data->map_data.map_width && mm.j >= 0 && \
			data->map_data.map[mm.i][mm.j] == '1')
		my_mlx_pixel_put(&data->img, mm.start_x, mm.start_y, mm.color);
	else if (mm.i < data->map_data.map_height && mm.i >= 0 \
		&& mm.j < data->map_data.map_width && mm.j >= 0 && \
		data->map_data.map[mm.i][mm.j] == '0')
		my_mlx_pixel_put(&data->img, mm.start_x, mm.start_y, 0);
	else
		my_mlx_pixel_put(&data->img, mm.start_x, mm.start_y, mm.color_);
}

void	mini_map(t_data *data)
{
	t_mini_map	mm;

	mm.start_y = -1;
	mm.map_y = data->player.y_pos - 125;
	mm.color = (255 * pow(2, 16)) + (255 * pow(2, 8)) + 255;
	mm.color_ = (255 * pow(2, 16)) + (0 * pow(2, 8)) + 0;
	while (++mm.start_y < 250)
	{
		mm.start_x = -1;
		mm.map_x = data->player.x_pos - 125;
		while (++mm.start_x < 250)
		{
			mm.i = (int)mm.map_y >> (int)WALL_SHIFT;
			mm.j = (int)mm.map_x >> (int)WALL_SHIFT;
			put_the_mini_map(data, mm);
			mm.map_x++;
		}
		mm.map_y++;
	}
	draw_mini_cube(data, 125, 125, mm.color_);
}

int	mouse_hook(t_data *data)
{
	int	x;
	int	y;

	if (!data->mouse_app)
	{
		if (mlx_mouse_get_pos(data->mlx_win, &x, &y) == -1)
			free_all_fatal("Rycasting: mlx_mouse_get_pos() failed", data);
		if (x != W_WIDTH / 2)
		{
			if (x > W_WIDTH / 2)
				rotate_right(data);
			else
				rotate_left(data);
		}
		if (mlx_mouse_move(data->mlx_win, W_WIDTH / 2, W_HEIGHT / 2) == -1)
			free_all_fatal("Rycasting: mlx_mouse_move() failed", data);
	}
	return (0);
}
