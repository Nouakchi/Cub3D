/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_cast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:37:41 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:53:09 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static double	check_horz_inter(t_data *data)
{
	int	i;
	int	j;

	data->ray.x_step = WALL_HEIGHT / tan(data->ray.angle * (M_PI / 180.0));
	data->ray.y_step = -WALL_HEIGHT;
	data->ray.y_h_inter = ((int)floor((int)data->player.y_pos >> \
		(int)WALL_SHIFT) << (int)WALL_SHIFT);
	data->ray.x_h_inter = data->player.x_pos + (data->player.y_pos \
		- data->ray.y_h_inter) / tan(data->ray.angle * (M_PI / 180.0));
	i = (int)(data->ray.y_h_inter - 1) >> (int)WALL_SHIFT;
	j = (int)data->ray.x_h_inter >> (int)WALL_SHIFT;
	while (i < data->map_data.map_height && i >= 0
		&& j < data->map_data.map_width && j >= 0
		&& data->map_data.map[i][j] != '1')
	{
		data->ray.y_h_inter += data->ray.y_step;
		data->ray.x_h_inter += data->ray.x_step;
		i = (int)(data->ray.y_h_inter - 1) >> (int)WALL_SHIFT;
		j = (int)data->ray.x_h_inter >> (int)WALL_SHIFT;
	}
	return ((double)fabs(data->player.y_pos - data->ray.y_h_inter)
		/ sin(data->ray.angle * (M_PI / 180.0)));
}

static void	get_first_inter(t_data *data)
{
	double	tmp;

	data->ray.x_step = WALL_HEIGHT;
	data->ray.y_step = WALL_HEIGHT * tan(data->ray.angle * (M_PI / 180.0));
	if (data->ray.angle >= 90)
		data->ray.x_step *= -1;
	tmp = 0;
	if (data->ray.angle < 90)
		tmp = WALL_HEIGHT;
	data->ray.x_v_inter = ((int)floor((int)data->player.x_pos >> \
		(int)WALL_SHIFT) << (int)WALL_SHIFT) + tmp;
	data->ray.y_v_inter = data->player.y_pos - ((data->ray.x_v_inter \
		- data->player.x_pos) * tan(data->ray.angle * (M_PI / 180.0)));
}

static double	check_vert_inter(t_data *data)
{
	int	i;
	int	j;

	get_first_inter(data);
	i = (int)data->ray.y_v_inter >> (int)WALL_SHIFT;
	j = (int)(data->ray.x_v_inter + 1) >> (int)WALL_SHIFT;
	if (data->ray.angle >= 90)
		j--;
	while (i < data->map_data.map_height && i >= 0
		&& j < data->map_data.map_width && j >= 0
		&& data->map_data.map[i][j] != '1')
	{
		if (data->ray.angle < 90)
			data->ray.y_v_inter -= data->ray.y_step;
		else
			data->ray.y_v_inter += data->ray.y_step;
		data->ray.x_v_inter += data->ray.x_step;
		i = (int)data->ray.y_v_inter >> (int)WALL_SHIFT;
		j = (int)(data->ray.x_v_inter + 1) >> (int)WALL_SHIFT;
		if (data->ray.angle >= 90)
			j--;
	}
	return ((double)fabs(data->player.y_pos - data->ray.y_v_inter)
		/ sin(data->ray.angle * (M_PI / 180.0)));
}

static void	get_correct_ray(t_data *data, double *ray)
{
	double	horz_dist;
	double	vert_dist;

	horz_dist = check_horz_inter(data);
	vert_dist = check_vert_inter(data);
	*ray = horz_dist;
	data->ray.is_vert = 0;
	data->ray.x_inter = data->ray.x_h_inter;
	data->ray.y_inter = data->ray.y_h_inter;
	if (*ray > vert_dist)
	{
		*ray = vert_dist;
		data->ray.is_vert = 1;
		data->ray.x_inter = data->ray.x_v_inter;
		data->ray.y_inter = data->ray.y_v_inter;
	}
}

int	up_cast(t_data *data, int start, double beta_angle)
{
	double	ray;
	t_cond	cond;

	get_correct_ray(data, &ray);
	check_0_degrees(data, &ray);
	ray = fabs((double)ray * cos(beta_angle * (M_PI / 180.0)));
	cond.ac_h = ceil((WALL_HEIGHT * DIST_TO_PROJ) / ray);
	cond.x_start = start;
	cond.y_start = (W_HEIGHT / 2) - (cond.ac_h / 2);
	cond.y_end = fabs((W_HEIGHT / 2) - (cond.ac_h / 2)) + cond.ac_h;
	draw_line(data, cond);
	return (0);
}
