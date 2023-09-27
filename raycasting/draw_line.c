/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:49:26 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 10:45:21 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	get_start_index(t_data *data)
{
	int	start_index;

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
	return (start_index);
}

static unsigned int	get_color_cf(t_data *data, int top)
{
	if (top)
		return ((data->map_data.map_elements.crgb.r * pow(2, 16)) \
			+ (data->map_data.map_elements.crgb.g * pow(2, 8)) \
			+ data->map_data.map_elements.crgb.b);
	else
		return ((data->map_data.map_elements.frgb.r * pow(2, 16)) \
			+ (data->map_data.map_elements.frgb.g * pow(2, 8)) \
			+ data->map_data.map_elements.frgb.b);
}

static void	get_color_w(t_data *data, int in, int start_index, \
		unsigned int *color)
{
	if (data->ray.angle == 0)
		*color = data->map_data.map_elements.colors_east[in][start_index];
	else
	{
		if (!data->ray.is_vert)
		{
			if (data->ray.angle <= 180 && data->ray.angle > 0)
				*color = data->map_data.map_elements.colors_north \
					[in][start_index];
			else
				*color = data->map_data.map_elements.colors_south \
					[in][start_index];
		}
		else
		{
			if (data->ray.angle >= 90 && data->ray.angle <= 270)
				*color = data->map_data.map_elements.colors_west \
					[in][start_index];
			else
				*color = data->map_data.map_elements.colors_east \
					[in][start_index];
		}
	}
}

static void	draw_line_helper(t_data *data, t_cond *c, t_draw_l *d)
{
	d->i = 0;
	while (d->i < c->y_start)
		my_mlx_pixel_put(&data->img, c->x_start, d->i++, d->color);
	while (c->y_start <= c->y_end)
	{
		get_color_w(data, d->in, d->start_index, &d->color);
		if (c->ac_h == 0)
			c->ac_h = 1;
		d->total += ((float)WALL_HEIGHT / (float)c->ac_h);
		d->in = (int)d->total;
		if (d->in > WALL_HEIGHT - 1)
			d->in = 0;
		my_mlx_pixel_put(&data->img, c->x_start, c->y_start++, d->color);
	}
	d->color = get_color_cf(data, 0);
	while (c->y_start < W_HEIGHT)
		my_mlx_pixel_put(&data->img, c->x_start, c->y_start++, d->color);
}

void	draw_line(t_data *data, t_cond c)
{
	t_draw_l	d;

	d.total = 0;
	if (c.ac_h > W_HEIGHT)
		d.total = (((float)c.ac_h - W_HEIGHT) / 2.0) * \
			(WALL_HEIGHT / (float)c.ac_h);
	d.in = (int)d.total;
	if (c.y_end >= W_HEIGHT)
		c.y_end = W_HEIGHT - 1;
	if (c.y_start < 0)
		c.y_start = 0;
	d.start_index = get_start_index(data);
	d.color = get_color_cf(data, 1);
	draw_line_helper(data, &c, &d);
}
