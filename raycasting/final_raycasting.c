/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:32:02 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/22 03:56:21 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void draw_line(t_data *data, int x_start, int y_start, int y_end, int actual_height)
{
	int i;
	unsigned int color;
	float total;
	int start_index;
	int in;
	
	if (data->ray.is_vert || !data->ray.angle)
	{
		start_index = (int)data->ray.y_inter % 64;
		if (data->ray.y_inter < 0)
			start_index = 0;
	}
	else
	{
		start_index = (int)data->ray.x_inter % 64;
		if (data->ray.x_inter < 0)
			start_index = 0;
	}
	total = 0;
	if (actual_height > 512)
		total = (((float) actual_height - 512.0) / 2.0) * (64.0 / (float) actual_height);
	in = (int)total;
	if (y_end >= 512)
		y_end = 511;
	if (y_start < 0)
		y_start = 0;
	color = (data->map_data.map_elements.crgb.r * 65536) + (data->map_data.map_elements.crgb.g * 256) + data->map_data.map_elements.crgb.b;
	i = 0;
	while (i < y_start)
		my_mlx_pixel_put(&data->img, x_start, i++, color);

	while (y_start <= y_end)
	{
		if (data->ray.angle == 0)
			color = data->map_data.map_elements.colors_east[in][start_index];
		else
		{
			if (!data->ray.is_vert)
			{
				if (data->ray.angle <= 180 && data->ray.angle > 0)
					color = data->map_data.map_elements.colors_north[in][start_index];
				else
					color = data->map_data.map_elements.colors_south[in][start_index];
			}
			else
			{
				if (data->ray.angle >= 90 && data->ray.angle <= 270)
					color = data->map_data.map_elements.colors_west[in][start_index];
				else
					color = data->map_data.map_elements.colors_east[in][start_index];
			}
		}
		if (actual_height == 0)
			actual_height = 1;
		total += ( (float) 64 / (float) actual_height);
		in = (int)total;
		if (in > 63)
			in = 0;
		my_mlx_pixel_put(&data->img, x_start, y_start++, color);
	}
	color = (data->map_data.map_elements.frgb.r * 65536) + (data->map_data.map_elements.frgb.g * 256) + data->map_data.map_elements.frgb.b;
	while (y_start < 512)
		my_mlx_pixel_put(&data->img, x_start, y_start++, color);
}

void	get_first_horz_inter(t_data *data, int *i, int *j)
{
	double	chart;
	
	data->ray.x_step = fabs(64 / tan(data->ray.angle * (M_PI / 180.0)));
    data->ray.y_step = 64;

    data->ray.y_h_inter = ((int)floor((int)data->player.y_pos >> (int)WALL_SHIFT) << (int)WALL_SHIFT) + data->ray.y_step - .02;
	chart = fabs(fabs(data->player.y_pos - data->ray.y_h_inter) / tan(data->ray.angle * (M_PI / 180.0)));
    data->ray.x_h_inter = data->player.x_pos - chart;
	if (data->ray.angle < 90 || data->ray.angle >= 270)
		data->ray.x_h_inter = data->player.x_pos + chart;

    *i = (int)data->ray.y_h_inter  >> (int)WALL_SHIFT;
	*j = (int)data->ray.x_h_inter  >> (int)WALL_SHIFT;
	if (data->ray.angle > 180 && data->ray.angle < 360)
		(*i)++;

}

double	d_check_horz_inter(t_data *data)
{
	int		i;
	int		j;
	
	get_first_horz_inter(data, &i, &j);
    while (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width && j >= 0 && data->map_data.map[i][j] != '1')
	{
		data->ray.y_h_inter += data->ray.y_step;
		if (data->ray.angle < 90 || data->ray.angle >= 270)
			data->ray.x_h_inter += data->ray.x_step;
		else
			data->ray.x_h_inter -= data->ray.x_step;
		i = (int)data->ray.y_h_inter >> (int)WALL_SHIFT;
		j = (int)data->ray.x_h_inter >> (int)WALL_SHIFT;

		if (data->ray.angle > 180 && data->ray.angle < 360)
			i++;
	}
	return (fabs(fabs(data->player.y_pos - data->ray.y_h_inter) / sin(data->ray.angle * (M_PI / 180.0))));
}

void	get_first_vert_inter(t_data *data, int *i, int *j)
{
	double	tmp;
	
	data->ray.x_step = 64;
    data->ray.y_step = fabs(64 * tan(data->ray.angle * (M_PI / 180.0)));
	tmp = 0;
	if ((data->ray.angle < 90 || data->ray.angle >= 270))
		tmp = 64;
    data->ray.x_v_inter = ((int)floor((int)data->player.x_pos >> (int)WALL_SHIFT) << (int)WALL_SHIFT) + tmp;
	data->ray.y_v_inter = fabs(data->player.y_pos + fabs(fabs(data->ray.x_v_inter - data->player.x_pos) * tan(data->ray.angle * (M_PI / 180.0))));
    *i = (int)data->ray.y_v_inter  >> (int)WALL_SHIFT;
	*j = (int)data->ray.x_v_inter  >> (int)WALL_SHIFT;
	if (data->ray.angle > 180 && data->ray.angle <= 270)
		(*j)--;
}

double d_check_vert_inter(t_data *data)
{
	int i;
	int j;
	get_first_vert_inter(data, &i, &j);
    while (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width  && j >= 0 && data->map_data.map[i][j] != '1')
	{
		if (data->ray.angle < 90 || data->ray.angle >= 270)
			data->ray.x_v_inter += data->ray.x_step;
		else
			data->ray.x_v_inter -= data->ray.x_step;
		data->ray.y_v_inter += data->ray.y_step;

		i = (int)data->ray.y_v_inter >> (int)WALL_SHIFT;
		j = (int)data->ray.x_v_inter >> (int)WALL_SHIFT;

		if (data->ray.angle > 180 && data->ray.angle <= 270)
			j--;
	}
	return (fabs(fabs(data->player.y_pos - data->ray.y_v_inter) / sin(data->ray.angle * (M_PI / 180.0))));
}

int	down_cast(t_data *data, int start, double beta_angle)
{
	double horz_dist;
	double vert_dist;
    // check horizontal intersection
	horz_dist = d_check_horz_inter(data);
	// check vertical
	vert_dist = d_check_vert_inter(data);
	// calculate ray distance
	double ray = horz_dist;
	data->ray.is_vert = 0;
	data->ray.x_inter = data->ray.x_h_inter;
	data->ray.y_inter = data->ray.y_h_inter;
	if (ray > vert_dist)
	{
		 ray = vert_dist;
		 data->ray.x_inter = data->ray.x_v_inter;
		 data->ray.y_inter = data->ray.y_v_inter;
		 data->ray.is_vert = 1;
	}
	// correct the fishbowl
	ray = fabs((double)ray * cos(beta_angle * (M_PI / 180.0)));
	// scale the ray
	double actual_height = ceil((64 * 886) / ray);
	draw_line(data, start, 256 - (actual_height / 2),
	fabs(256 - (actual_height / 2)) + actual_height, actual_height);
	return (0);
}
