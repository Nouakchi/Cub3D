/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:34:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:51:30 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	destroy_image_1(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_north.img);
}

void	destroy_image_2(t_data *data)
{
	destroy_image_1(data);
	mlx_destroy_image(data->mlx_ptr, data->img_south.img);
}

void	destroy_image_3(t_data *data)
{
	destroy_image_2(data);
	mlx_destroy_image(data->mlx_ptr, data->img_east.img);
}

void	destroy_image_4(t_data *data)
{
	destroy_image_3(data);
	mlx_destroy_image(data->mlx_ptr, data->img_west.img);
}
