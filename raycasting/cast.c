/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:11:35 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/21 00:27:07 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void update_data(t_data *data)
{
    printf("%f , %f , %f\n", data->player.view_angle, data->ray.angle, data->player.distance_to_wall);


    if (data->moves.move_f && data->player.distance_to_wall > 50)
    {
        if (data->player.view_angle <= 90 || data->player.view_angle >= 270)
            data->player.x_pos += 5 * cos(data->player.view_angle * (M_PI / 180));
        else
            data->player.x_pos += 5 * cos(data->player.view_angle * (M_PI / 180));
        if (data->player.view_angle >= 180)
            data->player.y_pos += 5 * fabs(sin(data->player.view_angle * (M_PI / 180)));
        else
            data->player.y_pos -= 5 * sin(data->player.view_angle * (M_PI / 180));
    }
    if (data->moves.move_b)
    {
        if (data->player.view_angle <= 90 || data->player.view_angle >= 270)
            data->player.x_pos -= 5 * cos(data->player.view_angle * (M_PI / 180));
        else
            data->player.x_pos += 5 * fabs(cos(data->player.view_angle * (M_PI / 180)));
        if (data->player.view_angle >= 180)
            data->player.y_pos += 5 * sin(data->player.view_angle * (M_PI / 180));
        else
            data->player.y_pos += 5 * sin(data->player.view_angle * (M_PI / 180));
    }
    if (data->moves.move_r)
    {
        if (data->ray.angle - 2 <= 0)
            data->ray.angle = 360 + (data->ray.angle - 2);
        else
            data->ray.angle -= 2;
        if (data->ray.angle <= 30)
            data->player.view_angle = 360 - (30 - data->ray.angle);
        else
            data->player.view_angle = data->ray.angle - 30;
        // if (data->player.view_angle < 0)
        //     data->player.view_angle = 360 - data->player.view_angle;

    }
    if (data->moves.move_l)
    {
        if (data->ray.angle + 2 >= 360)
            data->ray.angle = fabs(360 - (data->ray.angle + 2));
        else
            data->ray.angle += 2;
        if (data->ray.angle <= 30)
            data->player.view_angle = 360 - (30 - data->ray.angle);
        else
            data->player.view_angle = data->ray.angle - 30;
    }
}

int render(void *args)
{
    t_data *data = args;

    int start = -1;
	double beta_angle = 30;
    update_data(data);
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
			data->ray.angle = 360 - 0.05859375;
		else
			data->ray.angle -= 0.05859375;
		beta_angle -= 0.05859375;

	}
    data->ray.angle = angle;
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx_ptr, data->img.img);
    return (0);
}

int moves_press(int keycode, void *args)
{
    t_data *data;

    data = args;
    if (keycode == 2)
        data->moves.move_r = 1;
    else if (keycode == 0)
        data->moves.move_l = 1;
    else if (keycode == 13)
        data->moves.move_f = 1;
    else if (keycode == 1)
        data->moves.move_b = 1;
    return (0);
}

int moves_release(int keycode, void *args)
{
    t_data *data;

    data = args;
    if (keycode == 2)
        data->moves.move_r = 0;
    else if (keycode == 0)
        data->moves.move_l = 0;
    else if (keycode == 13)
        data->moves.move_f = 0;
    else if (keycode == 1)
        data->moves.move_b = 0;
    return (0);
}
