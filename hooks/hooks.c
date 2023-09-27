/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:52:37 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 05:15:34 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	moves_press_helper(int keycode, t_data *data)
{
	if (keycode == RIGHT_KEY)
		return (data->moves.move_r = 1, 1);
	else if (keycode == LEFT_KEY)
		return (data->moves.move_l = 1, 1);
	else if (keycode == UP_KEY)
		return (data->moves.move_f = 1, 1);
	else if (keycode == DOWN_KEY)
		return (data->moves.move_b = 1, 1);
	else if (keycode == QUIT_KEY)
		free_all_success(data);
	else if (keycode == ROTATE_L)
		return (data->moves.rotate_l = 1, 1);
	else if (keycode == ROTATE_R)
		return (data->moves.rotate_r = 1, 1);
	return (0);
}

int	moves_press(int keycode, void *args)
{
	t_data	*data;

	data = args;
	if (moves_press_helper(keycode, data))
		return (0);
	else if (keycode == 49)
	{
		data->mouse_app = !data->mouse_app;
		if (!data->mouse_app)
		{
			if (mlx_mouse_hide() == -1)
				free_all_fatal("Rycasting: mlx_mouse_hide() failed", data);
		}
		else
			if (mlx_mouse_show() == -1)
				free_all_fatal("Rycasting: mlx_mouse_show() failed", data);
	}
	return (0);
}

int	moves_release(int keycode, void *args)
{
	t_data	*data;

	data = args;
	if (keycode == RIGHT_KEY)
		data->moves.move_r = 0;
	else if (keycode == LEFT_KEY)
		data->moves.move_l = 0;
	else if (keycode == UP_KEY)
		data->moves.move_f = 0;
	else if (keycode == DOWN_KEY)
		data->moves.move_b = 0;
	if (keycode == ROTATE_R)
		data->moves.rotate_r = 0;
	else if (keycode == ROTATE_L)
		data->moves.rotate_l = 0;
	return (0);
}

