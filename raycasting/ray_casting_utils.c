/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:51:25 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 05:04:06 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_0_degrees(t_data *data, double *ray)
{
	if (data->ray.angle - DIFF_RAYS == 0 || data->ray.angle + DIFF_RAYS == 180)
	{
		data->last_ray = *ray;
		data->last_x_inter = data->ray.x_inter;
		data->last_y_inter = data->ray.y_inter;
	}
	if (data->ray.angle == 0 || data->ray.angle == 180)
	{
		*ray = data->last_ray;
		data->ray.x_inter = data->last_x_inter;
		data->ray.y_inter = data->last_y_inter;
	}
}

int	check_exit(t_data *data, double *pos_x, double *pos_y)
{
	if ((data->player.view_angle >= 0 && data->player.view_angle <= 90) \
		|| (data->player.view_angle > 180 && data->player.view_angle <= 270))
		if (data->map_data.map[(int)(*pos_y + 8) >> \
		(int)WALL_SHIFT][(int)(*pos_x + 8) >> (int)WALL_SHIFT] == '1' \
		&& data->map_data.map[(int)(*pos_y - 8) >> \
		(int)WALL_SHIFT][(int)(*pos_x - 8) >> (int)WALL_SHIFT] == '1')
			return (1);
	if ((data->player.view_angle > 90 && data->player.view_angle <= 180) \
		|| (data->player.view_angle > 270 && data->player.view_angle <= 360))
		if (data->map_data.map[(int)(*pos_y - 8) >> \
			(int)WALL_SHIFT][(int)(*pos_x + 8) >> (int)WALL_SHIFT] == '1' \
			&& data->map_data.map[(int)(*pos_y + 8) >> \
			(int)WALL_SHIFT][(int)(*pos_x - 8) >> (int)WALL_SHIFT] == '1')
			return (1);
	return (0);
}

