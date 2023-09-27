/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:32:02 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 01:54:12 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_line(t_data *data, int x_start, int y_start, int y_end,
		int actual_height)
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
	if (actual_height > W_HEIGHT)
		total = (((float)actual_height - W_HEIGHT) / 2.0) * \
			(WALL_HEIGHT / (float)actual_height);
	in = (int)total;
	if (y_end >= W_HEIGHT)
		y_end = W_HEIGHT - 1;
	if (y_start < 0)
		y_start = 0;
	color = (data->map_data.map_elements.crgb.r * pow(2, 16))
		+ (data->map_data.map_elements.crgb.g * pow(2, 8))
		+ data->map_data.map_elements.crgb.b;
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
		if (actual_height == 0)
			actual_height = 1;
		total += ((float)WALL_HEIGHT / (float)actual_height);
		in = (int)total;
		if (in > WALL_HEIGHT - 1)
			in = 0;
		my_mlx_pixel_put(&data->img, x_start, y_start++, color);
	}
	color = (data->map_data.map_elements.frgb.r * pow(2, 16))
		+ (data->map_data.map_elements.frgb.g * pow(2, 8))
		+ data->map_data.map_elements.frgb.b;
	while (y_start < W_HEIGHT)
		my_mlx_pixel_put(&data->img, x_start, y_start++, color);
}

void	get_first_horz_inter(t_data *data, int *i, int *j)
{
	double	chart;

	data->ray.x_step = fabs(WALL_HEIGHT / tan(data->ray.angle \
		* (M_PI / 180.0)));
	data->ray.y_step = WALL_HEIGHT;
	data->ray.y_h_inter = ((int)floor((int)data->player.y_pos \
		>> (int)WALL_SHIFT) << (int)WALL_SHIFT)
		+ data->ray.y_step;
	chart = fabs(fabs(data->player.y_pos - data->ray.y_h_inter) \
		/ tan(data->ray.angle * (M_PI / 180.0)));
	data->ray.x_h_inter = data->player.x_pos - chart;
	if (data->ray.angle < 90 || data->ray.angle >= 270)
		data->ray.x_h_inter = data->player.x_pos + chart;
	*i = (int)(data->ray.y_h_inter - 1) >> (int)WALL_SHIFT;
	*j = (int)data->ray.x_h_inter >> (int)WALL_SHIFT;
	if (data->ray.angle > 180 && data->ray.angle < 360)
		(*i)++;
}

double	d_check_horz_inter(t_data *data)
{
	int	i;
	int	j;

	get_first_horz_inter(data, &i, &j);
	while (i < data->map_data.map_height && i >= 0
		&& j < data->map_data.map_width && j >= 0
		&& data->map_data.map[i][j] != '1')
	{
		data->ray.y_h_inter += data->ray.y_step;
		if (data->ray.angle < 90 || data->ray.angle >= 270)
			data->ray.x_h_inter += data->ray.x_step;
		else
			data->ray.x_h_inter -= data->ray.x_step;
		i = (int)(data->ray.y_h_inter - 1) >> (int)WALL_SHIFT;
		j = (int)data->ray.x_h_inter >> (int)WALL_SHIFT;
		if (data->ray.angle > 180 && data->ray.angle < 360)
			i++;
	}
	return (fabs(fabs(data->player.y_pos - data->ray.y_h_inter)
			/ sin(data->ray.angle * (M_PI / 180.0))));
}

void	get_first_vert_inter(t_data *data, int *i, int *j)
{
	double	tmp;

	data->ray.x_step = WALL_HEIGHT;
	data->ray.y_step = fabs(WALL_HEIGHT * \
		tan(data->ray.angle * (M_PI / 180.0)));
	tmp = 0;
	if ((data->ray.angle < 90 || data->ray.angle >= 270))
		tmp = WALL_HEIGHT;
	data->ray.x_v_inter = ((int)floor((int)data->player.x_pos \
		>> (int)WALL_SHIFT) << (int)WALL_SHIFT)
		+ tmp;
	data->ray.y_v_inter = fabs(data->player.y_pos \
		+ fabs(fabs(data->ray.x_v_inter - data->player.x_pos) \
		* tan(data->ray.angle * (M_PI / 180.0))));
	*i = (int)data->ray.y_v_inter >> (int)WALL_SHIFT;
	*j = (int)(data->ray.x_v_inter + 1) >> (int)WALL_SHIFT;
	if (data->ray.angle > 180 && data->ray.angle <= 270)
		(*j)--;
}

double	d_check_vert_inter(t_data *data)
{
	int	i;
	int	j;

	get_first_vert_inter(data, &i, &j);
	while (i < data->map_data.map_height && i >= 0
		&& j < data->map_data.map_width && j >= 0
		&& data->map_data.map[i][j] != '1')
	{
		if (data->ray.angle < 90 || data->ray.angle >= 270)
			data->ray.x_v_inter += data->ray.x_step;
		else
			data->ray.x_v_inter -= data->ray.x_step;
		data->ray.y_v_inter += data->ray.y_step;
		i = (int)data->ray.y_v_inter >> (int)WALL_SHIFT;
		j = (int)(data->ray.x_v_inter + 1) >> (int)WALL_SHIFT;
		if (data->ray.angle > 180 && data->ray.angle <= 270)
			j--;
	}
	return (fabs(fabs(data->player.y_pos - data->ray.y_v_inter)
			/ sin(data->ray.angle * (M_PI / 180.0))));
}

int	down_cast(t_data *data, int start, double beta_angle)
{
	double	horz_dist;
	double	vert_dist;
	double	ray;
	double	actual_height;

	horz_dist = d_check_horz_inter(data);
	vert_dist = d_check_vert_inter(data);
	ray = horz_dist;
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
	ray = fabs((double)ray * cos(beta_angle * (M_PI / 180.0)));
	actual_height = ceil((WALL_HEIGHT * DIST_TO_PROJ) / ray);
	draw_line(data, start, (W_HEIGHT / 2) - (actual_height / 2), fabs((W_HEIGHT
				/ 2) - (actual_height / 2)) + actual_height, actual_height);
	return (0);
}
