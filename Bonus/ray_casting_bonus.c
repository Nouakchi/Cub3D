/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:31:37 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/27 07:44:31 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	cast_rays(t_data *data)
{
	int		start;
	double	beta_angle;

	start = -1;
	beta_angle = (FOV / 2);
	while (start < W_WIDTH - 1)
	{
		if (data->ray.angle > 180 && data->ray.angle < 360)
			down_cast(data, ++start, beta_angle);
		else
			up_cast(data, ++start, beta_angle);
		if (data->ray.angle <= 0)
			data->ray.angle = 360 - DIFF_RAYS;
		else
			data->ray.angle -= DIFF_RAYS;
		beta_angle -= DIFF_RAYS;
	}
}

int	render(void *args)
{
	t_data	*data;
	double	angle;

	data = args;
	update_data(data);
	mouse_hook(data);
	angle = data->ray.angle;
	data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!data->img.img)
		free_all_fatal("Rycasting: mlx_new_image() failed", data);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		free_all_fatal("Rycasting: mlx_get_data_addr() failed", data);
	cast_rays(data);
	mini_map(data);
	data->ray.angle = angle;
	if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
		data->img.img, 0, 0) == -1)
		free_all_fatal("Rycasting: mlx_put_image_to_window() failed", data);
	if (mlx_destroy_image(data->mlx_ptr, data->img.img) == -1)
		free_all_fatal("Rycasting: mlx_destroy_image() failed", data);
	return (0);
}
