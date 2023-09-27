/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:49:26 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:52:37 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_line(t_data *data, t_cond c)
{
	int				i;
	unsigned int	color;
	float			total;
	int				start_index;
	int				in;

	if (data->ray.is_vert || !data->ray.angle)
	{
		start_index = (int)data->ray.y_inter % (int)WALL_HEIGHT;
		if (data->ray.y_inter < 0)
			start_index = 0;
	}
	else
	{
		start_index = (int)data->ray.x_inter % (int)WALL_HEIGHT;
		if (data->ray.x_inter < 0)
			start_index = 0;
	}
	total = 0;
	if (c.ac_h > W_HEIGHT)
		total = (((float)c.ac_h - W_HEIGHT) / 2.0) * \
			(WALL_HEIGHT / (float)c.ac_h);
	in = (int)total;
	if (c.y_end >= W_HEIGHT)
		c.y_end = W_HEIGHT - 1;
	if (c.y_start < 0)
		c.y_start = 0;
	color = (data->map_data.map_elements.crgb.r * pow(2, 16))
		+ (data->map_data.map_elements.crgb.g * pow(2, 8))
		+ data->map_data.map_elements.crgb.b;
	i = 0;
	while (i < c.y_start)
		my_mlx_pixel_put(&data->img, c.x_start, i++, color);
	while (c.y_start <= c.y_end)
	{
		if (data->ray.angle == 0)
			color = data->map_data.map_elements.colors_east[in][start_index];
		else
		{
			if (!data->ray.is_vert)
			{
				if (data->ray.angle <= 180 && data->ray.angle > 0)
					color = data->map_data.map_elements.colors_north \
						[in][start_index];
				else
					color = data->map_data.map_elements.colors_south \
						[in][start_index];
			}
			else
			{
				if (data->ray.angle >= 90 && data->ray.angle <= 270)
					color = data->map_data.map_elements.colors_west \
						[in][start_index];
				else
					color = data->map_data.map_elements.colors_east \
						[in][start_index];
			}
		}
		if (c.ac_h == 0)
			c.ac_h = 1;
		total += ((float)WALL_HEIGHT / (float)c.ac_h);
		in = (int)total;
		if (in > WALL_HEIGHT - 1)
			in = 0;
		my_mlx_pixel_put(&data->img, c.x_start, c.y_start++, color);
	}
	color = (data->map_data.map_elements.frgb.r * pow(2, 16))
		+ (data->map_data.map_elements.frgb.g * pow(2, 8))
		+ data->map_data.map_elements.frgb.b;
	while (c.y_start < W_HEIGHT)
		my_mlx_pixel_put(&data->img, c.x_start, c.y_start++, color);
}
