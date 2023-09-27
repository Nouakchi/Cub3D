/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   down_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:32:02 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 05:30:13 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	get_first_horz_inter(t_data *data, int *i, int *j)
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

static double	d_check_horz_inter(t_data *data)
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

static void	get_first_vert_inter(t_data *data, int *i, int *j)
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

static double	d_check_vert_inter(t_data *data)
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
	t_cond	cond;

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
	cond.ac_h = ceil((WALL_HEIGHT * DIST_TO_PROJ) / ray);
	cond.x_start = start;
	cond.y_start = (W_HEIGHT / 2) - (cond.ac_h / 2);
	cond.y_end = fabs((W_HEIGHT / 2) - (cond.ac_h / 2)) + cond.ac_h;
	draw_line(data, cond);
	return (0);
}
