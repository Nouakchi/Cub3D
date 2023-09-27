/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 04:40:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 05:18:12 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static t_rgbt	calculate_color(t_img *img, int i, int j)
{
	t_rgbt	color;

	color.t = (unsigned char)img->addr[(i * img->line_length + j \
		* (img->bits_per_pixel / 8)) + 3];
	color.r = (unsigned char)img->addr[(i * img->line_length + j \
		* (img->bits_per_pixel / 8)) + 2];
	color.g = (unsigned char)img->addr[(i * img->line_length + j \
		* (img->bits_per_pixel / 8)) + 1];
	color.b = (unsigned char)img->addr[(i * img->line_length + j \
		* (img->bits_per_pixel / 8))];
	return (color);
}

static unsigned int	**get_color_img(t_img *img)
{
	int				i;
	int				j;
	t_rgbt			color;
	unsigned int	**map;

	i = 0;
	j = 0;
	map = malloc(sizeof(unsigned int *) * 64);
	if (!map)
		return (NULL);
	while (i < 64)
	{
		map[i] = malloc(sizeof(unsigned int) * 64);
		if (!map[i])
			return (NULL);
		j = 0;
		while (j < 64)
		{
			color = calculate_color(img, i, j);
			map[i][j] = color.t << 24 | color.r << 16 | color.g << 8 | color.b;
			j++;
		}
		i++;
	}
	return (map);
}

int	init_colors(t_data *data)
{
	data->map_data.map_elements.colors_north = get_color_img(&data->img_north);
	data->map_data.map_elements.colors_south = get_color_img(&data->img_south);
	data->map_data.map_elements.colors_east = get_color_img(&data->img_east);
	data->map_data.map_elements.colors_west = get_color_img(&data->img_west);
	if (!data->map_data.map_elements.colors_north
		|| !data->map_data.map_elements.colors_south
		|| !data->map_data.map_elements.colors_east
		|| !data->map_data.map_elements.colors_west)
		return (1);
	return (0);
}

void	free_color(unsigned int **color)
{
	int	i;

	i = -1;
	while (++i < 64)
		free(color[i]);
	free(color);
}

void	fatal(char *mssg)
{
	write(2, "Error\n", 6);
	write(2, mssg, ft_strlen(mssg));
	write(2, "\n", 1);
}