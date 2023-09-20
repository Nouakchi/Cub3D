/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:37:41 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/20 23:01:06 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int	up_cast(t_data *data, int start, double beta_angle)
{
    // char map[5][6] = {
	// 	{1,1,1,1,1,1},
	// 	{1,0,0,0,0,1},
	// 	{1,0,9,0,0,1},
	// 	{1,0,0,0,0,1},
	// 	{1,1,1,1,1,1},
	// };

    // check horizontal intersection

    data->ray.x_step = 64 / tan(data->ray.angle * (M_PI / 180.0));
    data->ray.y_step = -64;

    data->ray.y_h_inter = ((int)floor((int)data->player.y_pos >> (int)WALL_SHIFT) << (int)WALL_SHIFT) - 1;;
    data->ray.x_h_inter = data->player.x_pos + (data->player.y_pos - data->ray.y_h_inter) / tan(data->ray.angle * (M_PI / 180.0));

    int i = (int)data->ray.y_h_inter  >> (int)WALL_SHIFT;
	int j = (int)data->ray.x_h_inter  >> (int)WALL_SHIFT;

    while (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width && j >= 0 && data->map_data.map[i][j] != '1')
	{
		data->ray.y_h_inter += data->ray.y_step;
		data->ray.x_h_inter += data->ray.x_step;
		i = (int)data->ray.y_h_inter >> (int)WALL_SHIFT;
		j = (int)data->ray.x_h_inter >> (int)WALL_SHIFT;
	}

	double horz_dist = (double)fabs(data->player.y_pos - data->ray.y_h_inter) / sin(data->ray.angle * (M_PI / 180.0));
    // check vertical

    data->ray.x_step = 64;
    data->ray.y_step = 64 * tan(data->ray.angle * (M_PI / 180.0));

	if (data->ray.angle >= 90)
		data->ray.x_step *= -1;

    double tmp = (data->ray.angle < 90) ? 64 : 0;
    data->ray.x_v_inter = ((int)floor((int)data->player.x_pos >> (int)WALL_SHIFT) << (int)WALL_SHIFT) + tmp;
	data->ray.y_v_inter = data->player.y_pos - ((data->ray.x_v_inter - data->player.x_pos) * tan(data->ray.angle * (M_PI / 180.0)));


    i = (int)data->ray.y_v_inter  >> (int)WALL_SHIFT;
	j = (int)data->ray.x_v_inter  >> (int)WALL_SHIFT;

	if (data->ray.angle >= 90)
		j--;

    while (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width && j >= 0 && data->map_data.map[i][j] != '1')
	{
		if (data->ray.angle < 90 )
			data->ray.y_v_inter -= data->ray.y_step;
		else
			data->ray.y_v_inter += data->ray.y_step;
		data->ray.x_v_inter += data->ray.x_step;

		i = (int)data->ray.y_v_inter >> (int)WALL_SHIFT;
		j = (int)data->ray.x_v_inter >> (int)WALL_SHIFT;
		if (data->ray.angle >= 90)
			j--;
	}


	double vert_dist = (double)fabs(data->player.y_pos - data->ray.y_v_inter) / sin(data->ray.angle * (M_PI / 180.0));

	// calculate ray distance
	double ray = horz_dist;
	data->ray.is_vert = 0;
	data->ray.x_inter = data->ray.x_h_inter;
	data->ray.y_inter = data->ray.y_h_inter;
	if (ray > vert_dist)
	{
		ray = vert_dist;
		data->ray.is_vert = 1;
		data->ray.x_inter = data->ray.x_v_inter;
		data->ray.y_inter = data->ray.y_v_inter;
	}


	// correct the fishbowl
	ray = fabs((double)ray * cos(beta_angle * (M_PI / 180.0)));

	data->player.distance_to_wall = ray;

	// scale the ray

	double actual_height = ceil((64 * 886) / ray);





	draw_line(data, start, 256 - (actual_height / 2), fabs(256 - (actual_height / 2)) + actual_height, actual_height);

    return (0);
}
