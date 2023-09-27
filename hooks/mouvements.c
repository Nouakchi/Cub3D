/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:57:56 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:45:12 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	move_forward(t_data *data, double *pos_x, double *pos_y)
{
	double	next_pos_x;
	double	next_pos_y;

	*pos_x += SPEED * cos(data->player.view_angle * (M_PI / 180));
	if (data->player.view_angle >= 180)
		*pos_y += SPEED * fabs(sin(data->player.view_angle * (M_PI / 180)));
	else
		*pos_y -= SPEED * sin(data->player.view_angle * (M_PI / 180));
	next_pos_x = data->player.x_pos;
	next_pos_y = data->player.y_pos;
	if (data->map_data.map[(int)(*pos_y) >> \
		(int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
	{
		if (check_exit(data, pos_x, pos_y))
			return ;
		data->player.x_pos = *pos_x;
		data->player.y_pos = *pos_y;
	}
}

static void	move_backward(t_data *data, double *pos_x, double *pos_y)
{
	if (data->player.view_angle <= 90 || data->player.view_angle >= 270)
		*pos_x -= SPEED * cos(data->player.view_angle * (M_PI / 180));
	else
		*pos_x += SPEED * fabs(cos(data->player.view_angle * (M_PI / 180)));
	*pos_y += SPEED * sin(data->player.view_angle * (M_PI / 180));
	if (data->map_data.map[(int)(*pos_y) >> \
		(int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
	{
		data->player.x_pos = *pos_x;
		data->player.y_pos = *pos_y;
	}
}

static void	move_right(t_data *data, double *pos_x, double *pos_y)
{
	double	righ_view_angle;

	righ_view_angle = data->player.view_angle - 90;
	if (righ_view_angle < 0)
		righ_view_angle = 360 + (data->player.view_angle - 90);
	*pos_x += SPEED * cos(righ_view_angle * (M_PI / 180));
	if (righ_view_angle >= 180)
		*pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
	else
		*pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
	if (data->map_data.map[(int)(*pos_y) >> \
		(int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
	{
		if (check_exit(data, pos_x, pos_y))
			return ;
		data->player.x_pos = *pos_x;
		data->player.y_pos = *pos_y;
	}
}

static void	move_left(t_data *data, double *pos_x, double *pos_y)
{
	double	righ_view_angle;

	righ_view_angle = data->player.view_angle + 90;
	if (righ_view_angle >= 360)
		righ_view_angle = fabs(360 - (data->player.view_angle + 90));
	*pos_x += SPEED * cos(righ_view_angle * (M_PI / 180));
	if (righ_view_angle >= 180)
		*pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
	else
		*pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
	if (data->map_data.map[(int)(*pos_y) >> \
		(int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
	{
		if (check_exit(data, pos_x, pos_y))
			return ;
		data->player.x_pos = *pos_x;
		data->player.y_pos = *pos_y;
	}
}

void	update_data(t_data *data)
{
	double	pos_x ;
	double	pos_y;

	pos_x = data->player.x_pos;
	pos_y = data->player.y_pos;
	if (data->moves.move_f)
		move_forward(data, &pos_x, &pos_y);
	if (data->moves.move_b)
		move_backward(data, &pos_x, &pos_y);
	if (data->moves.move_r)
		move_right(data, &pos_x, &pos_y);
	if (data->moves.move_l)
		move_left(data, &pos_x, &pos_y);
	if (data->moves.rotate_r)
		rotate_right(data);
	if (data->moves.rotate_l)
		rotate_left(data);
}
