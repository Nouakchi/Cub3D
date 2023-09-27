/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 06:04:06 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 06:04:15 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	mlx_things(t_data *data)
{
	if (mouse_visibility(data))
		return (1);
	if (mlx_loop_hook(data->mlx_ptr, render, data) == -1)
		return (1);
	if (mlx_hook(data->mlx_win, 2, 0, moves_press, data) == -1)
		return (1);
	if (mlx_hook(data->mlx_win, 3, 0, moves_release, data) == -1)
		return (1);
	if (mlx_hook(data->mlx_win, 17, 0, free_all_success, data) == -1)
		return (1);
	if (mlx_loop(data->mlx_ptr) == -1)
		return (1);
	return (0);
}