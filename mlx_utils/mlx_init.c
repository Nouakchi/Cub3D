/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 06:02:47 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 06:04:28 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int	mlx_things(t_data *data)
{
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