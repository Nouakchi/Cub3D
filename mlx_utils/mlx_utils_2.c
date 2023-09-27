/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:37:43 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:43:08 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static int	error_img(t_data *data)
{
	if (!data->img_north.img)
		return (1);
	if (!data->img_south.img)
		return (destroy_image_1(data), 1);
	if (!data->img_east.img)
		return (destroy_image_2(data), 1);
	if (!data->img_west.img)
		return (destroy_image_3(data), 1);
	return (0);
}

static int	error_addr(t_data *data)
{
	if (!data->img_north.addr)
		return (destroy_image_4(data), 1);
	if (!data->img_south.addr)
		return (destroy_image_4(data), 1);
	if (!data->img_east.addr)
		return (destroy_image_4(data), 1);
	if (!data->img_west.addr)
		return (destroy_image_4(data), 1);
	return (0);
}

int	init_textures(t_data *data, int size)
{
	data->img_north.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->map_data.map_elements.north_text, &size, &size);
	data->img_south.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->map_data.map_elements.south_text, &size, &size);
	data->img_east.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->map_data.map_elements.east_text, &size, &size);
	data->img_west.img = mlx_xpm_file_to_image(data->mlx_ptr, \
		data->map_data.map_elements.west_text, &size, &size);
	if (error_img(data))
		return (1);
	data->img_north.addr = mlx_get_data_addr(data->img_north.img, \
		&data->img_north.bits_per_pixel, &data->img_north.line_length, \
		&data->img_north.endian);
	data->img_south.addr = mlx_get_data_addr(data->img_south.img, \
		&data->img_south.bits_per_pixel, &data->img_south.line_length, \
		&data->img_south.endian);
	data->img_east.addr = mlx_get_data_addr(data->img_east.img, \
		&data->img_east.bits_per_pixel, &data->img_east.line_length, \
		&data->img_east.endian);
	data->img_west.addr = mlx_get_data_addr(data->img_west.img, \
		&data->img_west.bits_per_pixel, &data->img_west.line_length, \
		&data->img_west.endian);
	if (error_addr(data))
		return (1);
	return (0);
}

int	init_my_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
	if (!data->mlx_win)
		return (1);
	return (0);
}

void	free_element_mlx(t_data *data)
{
	free_element_(data);
	if (mlx_destroy_window(data->mlx_ptr, data->mlx_win) == -1)
		fatal("MLX failed");
}
