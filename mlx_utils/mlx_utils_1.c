/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:34:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 08:47:03 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	destroy_images(t_data *data)
{
	if (data->img_north.img)
		mlx_destroy_image(data->mlx_ptr, data->img_north.img);
	if (data->img_south.img)
		mlx_destroy_image(data->mlx_ptr, data->img_south.img);
	if (data->img_east.img)
		mlx_destroy_image(data->mlx_ptr, data->img_east.img);
	if (data->img_west.img)
		mlx_destroy_image(data->mlx_ptr, data->img_west.img);
}
