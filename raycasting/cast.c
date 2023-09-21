/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:11:35 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/21 09:02:40 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void update_data(t_data *data)
{
    
    double pos_x = data->player.x_pos;
    double pos_y = data->player.y_pos;

    if (data->moves.move_f)
    {
        if (data->player.view_angle <= 90 || data->player.view_angle >= 270)
            pos_x += 8 * cos(data->player.view_angle * (M_PI / 180));
        else
            pos_x += 8 * cos(data->player.view_angle * (M_PI / 180));
        if (data->player.view_angle >= 180)
            pos_y += 8 * fabs(sin(data->player.view_angle * (M_PI / 180)));
        else
            pos_y -= 8 * sin(data->player.view_angle * (M_PI / 180));
        if (data->map_data.map[(int)(pos_y) >> (int)WALL_SHIFT][(int)(pos_x) >> (int)WALL_SHIFT] != '1')
        {
            data->player.x_pos = pos_x;
            data->player.y_pos = pos_y;
        }
    }
    if (data->moves.move_b)
    {
        if (data->player.view_angle <= 90 || data->player.view_angle >= 270)
            pos_x -= 8 * cos(data->player.view_angle * (M_PI / 180));
        else
            pos_x += 8 * fabs(cos(data->player.view_angle * (M_PI / 180)));
        if (data->player.view_angle >= 180)
            pos_y += 8 * sin(data->player.view_angle * (M_PI / 180));
        else
            pos_y += 8 * sin(data->player.view_angle * (M_PI / 180));
        if (data->map_data.map[(int)(pos_y) >> (int)WALL_SHIFT][(int)(pos_x) >> (int)WALL_SHIFT] != '1')
        {
            data->player.x_pos = pos_x;
            data->player.y_pos = pos_y;
        }
    }
    if (data->moves.move_r)
    {
        if (data->ray.angle - (35 * 0.05859375) <= 0)
            data->ray.angle = 360 + (data->ray.angle - (35 * 0.05859375));
        else
            data->ray.angle -= (35 * 0.05859375);
        if (data->ray.angle <= 30)
            data->player.view_angle = 360 - (30 - data->ray.angle);
        else
            data->player.view_angle = data->ray.angle - 30;

    }
    if (data->moves.move_l)
    {
        if (data->ray.angle + (35 * 0.05859375) >= 360)
            data->ray.angle = fabs(360 - (data->ray.angle + (35 * 0.05859375)));
        else
            data->ray.angle += (35 * 0.05859375);
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
		if (data->ray.angle > 180 && data->ray.angle < 360)
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
    // pause();
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
