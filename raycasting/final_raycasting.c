/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:32:02 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/18 15:44:42 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void draw_line(t_data *data, int x_start, int y_start, int y_end, int actual_height)
{
	// (void)actual_height;
	int i = 0;
	unsigned int color = 0x00FF0000;
	float total = 0;

	int start_index_j = (int)data->ray.y_inter % 64;
	int start_index_i = (int)data->ray.x_inter % 64;
	int start_index;
	if (start_index_i > start_index_j)
		start_index = start_index_i;
	else
		start_index = start_index_j;

	// printf("start_index_i = %d\n", start_index_i);
	// printf("start_index_j = %d\n", start_index_j);


	int in;
	if (actual_height > 512)
	{
		total = (((float) actual_height - 512.0) / 2.0) * (64.0 / (float) actual_height);
	}
	else
		total = 0;
	in = (int)total;
	if (y_end >= 512)
		y_end = 511;
	if (y_start < 0)
		y_start = 0;

	while (i < y_start)
		my_mlx_pixel_put(&data->img, x_start, i++, 0x000000FF);

	while (y_start <= y_end)
	{


		color = data->map_data.map_elements.colors_north[in][start_index];

		if (actual_height == 0)
			actual_height = 1;
		total += ( (float) 64 / (float) actual_height);
		in = (int)total;
		if (in > 63)
			in = 0;
		my_mlx_pixel_put(&data->img, x_start, y_start++, color);
	}

	while (y_start < 512)
		my_mlx_pixel_put(&data->img, x_start, y_start++, 0x0000FF00);
}

int	down_cast(t_data *data, int start, double beta_angle)
{
    // char map[5][6] = {
	// 	{1,1,1,1,1,1},
	// 	{1,0,0,0,0,1},
	// 	{1,0,9,0,0,1},
	// 	{1,0,0,0,0,1},
	// 	{1,1,1,1,1,1},
	// };


    // check horizontal intersection

    data->ray.x_step = fabs(64 / tan(data->ray.angle * (M_PI / 180.0)));
    data->ray.y_step = 64;

    data->ray.y_inter = ((int)floor((int)data->player.y_pos >> (int)WALL_SHIFT) << (int)WALL_SHIFT) + data->ray.y_step - .02;
	double chart = fabs(fabs(data->player.y_pos - data->ray.y_inter) / tan(data->ray.angle * (M_PI / 180.0)));
    data->ray.x_inter = data->player.x_pos - chart;
	if (data->ray.angle < 90 || data->ray.angle > 270)
		data->ray.x_inter = data->player.x_pos + chart;

    int i = (int)data->ray.y_inter  >> (int)WALL_SHIFT;
	int j = (int)data->ray.x_inter  >> (int)WALL_SHIFT;

	if (data->ray.angle > 180 && data->ray.angle < 360)
		i++;

    while (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width && j >= 0 && data->map_data.map[i][j] != '1')
	{
		data->ray.y_inter += data->ray.y_step;
		if (data->ray.angle < 90 || data->ray.angle > 270)
			data->ray.x_inter += data->ray.x_step;
		else
			data->ray.x_inter -= data->ray.x_step;
		i = (int)data->ray.y_inter >> (int)WALL_SHIFT;
		j = (int)data->ray.x_inter >> (int)WALL_SHIFT;

		if (data->ray.angle > 180 && data->ray.angle < 360)
			i++;
	}

	double horz_dist = fabs(fabs(data->player.y_pos - data->ray.y_inter) / sin(data->ray.angle * (M_PI / 180.0)));
	// check vertical

    data->ray.x_step = 64;
    data->ray.y_step = fabs(64 * tan(data->ray.angle * (M_PI / 180.0)));

	double tmp = (data->ray.angle < 90 || data->ray.angle > 270) ? 64 : 0;
    data->ray.x_inter = ((int)floor((int)data->player.x_pos >> (int)WALL_SHIFT) << (int)WALL_SHIFT) + tmp;
	data->ray.y_inter = fabs(data->player.y_pos + fabs(fabs(data->ray.x_inter - data->player.x_pos) * tan(data->ray.angle * (M_PI / 180.0))));


    i = (int)data->ray.y_inter  >> (int)WALL_SHIFT;
	j = (int)data->ray.x_inter  >> (int)WALL_SHIFT;

	if (data->ray.angle > 180 && data->ray.angle < 271)
		j--;

    while (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width  && j >= 0 && data->map_data.map[i][j] != '1')
	{
		if (data->ray.angle < 90 || data->ray.angle > 270)
			data->ray.x_inter += data->ray.x_step;
		else
			data->ray.x_inter -= data->ray.x_step;
		data->ray.y_inter += data->ray.y_step;

		i = (int)data->ray.y_inter >> (int)WALL_SHIFT;
		j = (int)data->ray.x_inter >> (int)WALL_SHIFT;

		if (data->ray.angle > 180 && data->ray.angle < 271)
			j--;
	}

	// calculate ray distance

	double vert_dist = fabs(fabs(data->player.y_pos - data->ray.y_inter) / sin(data->ray.angle * (M_PI / 180.0)));

	double ray = horz_dist;
	if (ray > vert_dist)
		ray = vert_dist;

	// correct the fishbowl

	ray = fabs((double)ray * cos(beta_angle * (M_PI / 180.0)));

	data->player.distance_to_wall = ray;

	// scale the ray

	double actual_height = ceil((64 * 886) / ray);

	draw_line(data, start, 256 - (actual_height / 2), fabs(256 - (actual_height / 2)) + actual_height, actual_height);





	return (0);
}
