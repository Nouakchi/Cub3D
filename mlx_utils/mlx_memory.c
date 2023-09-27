/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:41:27 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:51:16 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_element_(t_data *data)
{
	if (data->map_data.map_elements.colors_north)
		free_color(data->map_data.map_elements.colors_north);
	if (data->map_data.map_elements.colors_south)
		free_color(data->map_data.map_elements.colors_south);
	if (data->map_data.map_elements.colors_east)
		free_color(data->map_data.map_elements.colors_east);
	if (data->map_data.map_elements.colors_west)
		free_color(data->map_data.map_elements.colors_west);
	if (data->map_data.map_elements.north_text)
		free(data->map_data.map_elements.north_text);
	if (data->map_data.map_elements.south_text)
		free(data->map_data.map_elements.south_text);
	if (data->map_data.map_elements.east_text)
		free(data->map_data.map_elements.east_text);
	if (data->map_data.map_elements.west_text)
		free(data->map_data.map_elements.west_text);
	if (data->map_data.map)
		free_map(data->map_data.map);
}

void	free_element(t_data *data, int map_fd)
{
	free_element_(data);
	close(map_fd);
}

void	free_element_walls(t_data *data)
{
	destroy_image_4(data);
	free_element_(data);
}

void	free_all(t_data *data)
{
	free_element_walls(data);
	if (mlx_destroy_window(data->mlx_ptr, data->mlx_win) == -1)
		fatal("MLX failed");
}

void	free_all_fatal(char *msg, t_data *data)
{
	fatal(msg);
	free_all(data);
	exit(1);
}
