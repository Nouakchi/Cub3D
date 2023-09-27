/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 05:00:26 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:45:16 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate_right(t_data *data)
{
	if (data->ray.angle - (ROTATION * DIFF_RAYS) <= 0)
		data->ray.angle = 360 + (data->ray.angle - (ROTATION * DIFF_RAYS));
	else
		data->ray.angle -= (ROTATION * DIFF_RAYS);
	if (data->ray.angle <= (FOV / 2))
		data->player.view_angle = 360 - ((FOV / 2) - data->ray.angle);
	else
		data->player.view_angle = data->ray.angle - (FOV / 2);
}

void	rotate_left(t_data *data)
{
	if (data->ray.angle + (ROTATION * DIFF_RAYS) >= 360)
		data->ray.angle = fabs(360 - (data->ray.angle + \
			(ROTATION * DIFF_RAYS)));
	else
		data->ray.angle += (ROTATION * DIFF_RAYS);
	if (data->ray.angle <= (FOV / 2))
		data->player.view_angle = 360 - ((FOV / 2) - data->ray.angle);
	else
		data->player.view_angle = data->ray.angle - (FOV / 2);
}
