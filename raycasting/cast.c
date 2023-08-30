/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:11:35 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/30 21:30:23 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int render(void *args)
{
    t_data *data = args;
    
    int start = -1;
	double beta_angle = 30;
    double angle = 30;
	while (start < 1024)
	{
		// printf("%f\n", data.ray.angle);
		if (angle >= 180 && angle <= 360)
			down_cast(data, data->mlx_ptr, data->mlx_win , ++start, beta_angle);
		else
			up_cast(data, data->mlx_ptr, data->mlx_win , ++start, beta_angle);
		if (angle <= 0)
			angle = 360 - 0.05859375;
		else
			angle -= 0.05859375;
		beta_angle -= 0.05859375;
	}
    mlx_clear_window(data->mlx_ptr, data->mlx_win);
    return (0);
}

int moves(int keycode, void *args)
{
    t_data *data;

    data = args;
    if (keycode == 2)
    {
        printf("%d\n", keycode);
        printf("%f\n", data->ray.angle);
        // data->ray.angle -= 10;
    }
    // else
    return (0);
}