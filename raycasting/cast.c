/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:11:35 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/31 11:41:30 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int render(void *args)
{
    t_data *data = args;
    
    // mlx_clear_window(data->mlx_ptr, data->mlx_win);
   int start = -1;
	double beta_angle = 30;
    double angle = data->ray.angle;
    data->img.img = mlx_new_image(data->mlx_ptr, 1024, 512);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
							&data->img.endian);
    
	while (start < 1023)
	{
		if (data->ray.angle >= 180 && data->ray.angle <= 360)
			down_cast(data, ++start, beta_angle);
		else
			up_cast(data, ++start, beta_angle);
		if (data->ray.angle <= 0)
        {
			data->ray.angle = 360 - 0.05859375;
            // printf("%f\n", data->ray.angle);
            // getchar();
        }
		else
			data->ray.angle -= 0.05859375;
		beta_angle -= 0.05859375;
		
	}
    data->ray.angle = angle;
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->img.img);
    return (0);
}

int moves(int keycode, void *args)
{
    t_data *data;

    data = args;
    if (keycode == 2)
    {

        if (data->ray.angle - 20 <= 0)
            data->ray.angle = 360 + (data->ray.angle - 20);
        else
            data->ray.angle -= 20;
    }
    if (keycode == 0)
    {
        if (data->ray.angle + 20 >= 360)
            data->ray.angle = fabs(360 - (data->ray.angle + 20));
        else    
            data->ray.angle += 20;
    }
    return (0);
}