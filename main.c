/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/26 22:41:24 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fatal(char *mssg)
{
	write(2, "Error\n", 6);
	write(2, mssg, ft_strlen(mssg));
	write(2, "\n", 1);
}

void	data_map_init(t_data *data)
{
	data->map_data.map_elements.east_text = NULL;
	data->map_data.map_elements.west_text = NULL;
	data->map_data.map_elements.north_text = NULL;
	data->map_data.map_elements.south_text = NULL;
	data->map_data.map_elements.colors_east = NULL;
	data->map_data.map_elements.colors_west = NULL;
	data->map_data.map_elements.colors_north = NULL;
	data->map_data.map_elements.colors_south = NULL;
	data->map_data.map = NULL;
	data->img_north.img = NULL;
	data->img_south.img = NULL;
	data->img_east.img = NULL;
	data->img_west.img = NULL;
	data->map_data.map_elements.frgb.r = -1;
	data->map_data.map_elements.crgb.r = -1;
}

void	check(void)
{
	system("leaks cub3D");
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

int	error_img(t_data *data)
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

int	error_addr(t_data *data)
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

t_rgbt	calculate_color(t_img *img, int i, int j)
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

unsigned int	**get_color_img(t_img *img)
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

void	init_player_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->map_data.map_width = 0;
	while (data->map_data.map[++i])
	{
		j = -1;
		while (data->map_data.map[i][++j])
		{
			if (ft_strchr("NWSE", data->map_data.map[i][j]))
			{
				data->player.y_pos = i * 64 + 32;
				data->player.x_pos = j * 64 + 32;
				data->player.start_angle = data->map_data.map[i][j];
				data->map_data.map[i][j] = '0';
			}
		}
		if (data->map_data.map_width < (int)ft_strlen(data->map_data.map[i]))
			data->map_data.map_width = (int)ft_strlen(data->map_data.map[i]);
	}
	data->map_data.map_height = i;
}

void	init_angles_moves(t_data *data)
{
	if (data->player.start_angle == 'N')
		data->ray.angle = 120;
	else if (data->player.start_angle == 'W')
		data->ray.angle = 210;
	else if (data->player.start_angle == 'S')
		data->ray.angle = 300;
	else
		data->ray.angle = 30;
	data->player.view_angle = data->ray.angle - 30;
	data->moves.move_r = 0;
	data->moves.move_l = 0;
	data->moves.move_f = 0;
	data->moves.move_b = 0;
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

void free_all(t_data *data)
{
	free_element_walls(data);
	if (mlx_clear_window(data->mlx_ptr, data->mlx_win) == -1)
		fatal("MLX failed");
	if (mlx_destroy_window(data->mlx_ptr, data->mlx_win) == -1)
		fatal("MLX failed");
	// if (mlx_destroy_image(data->mlx_ptr, data->img.img) == -1) // WHY ERROR
	// 	fatal("MLX failed");
}

void	free_all_fatal(char *msg ,t_data *data)
{
	fatal(msg);
	free_all(data);
	exit(1);
}

int free_all_success(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

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

int	check_extension(int ac, char *av[])
{
	int	index;

	index = 0;
	if (ac != 2)
		return (fatal("Wrong number of arguments"), 1);
	if (ft_strlen(av[1]) < 5)
		return (fatal("Wrong file extension"), 1);
	else
	{
		index = ft_strlen(av[1]) - 1;
		if (av[1][index] != 'b' || av[1][index - 1] != 'u' || av[1][index
			- 2] != 'c' || av[1][index - 3] != '.')
			return (fatal("Wrong file extension"), 1);
	}
	return (0);
}

int	check_map_is_valid(int map_fd, t_data *data)
{
	if (!check_element(map_fd, data))
		return (1);
	if (check_map_pars(map_fd, data))
		return (1);
	return (0);
}

void check_()
{
	system("leaks cub3D");
}


int	main(int ac, char *av[])
{
	int		map_fd;
	t_data	data;

	// atexit(check_);
	if (check_extension(ac, av))
		return (fatal("Invalid arguments"), 1);
	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
		return (fatal("File opening failed"), 1);
	data_map_init(&data);
	if (check_map_is_valid(map_fd, &data))
		return (fatal("Map is not valid"), free_element(&data, map_fd), 1);
	trim_map(&data);
	if (close(map_fd) == -1)
		return (fatal("File closing failed"), free_element_(&data), 1);
	init_player_map(&data);
	if (init_my_mlx(&data))
		return (fatal("MLX failed"), free_element_(&data), 1);
	init_angles_moves(&data);
	if (init_textures(&data, 64))
		return (fatal("Textures failed"), free_element_(&data), 1);
	if (init_colors(&data))
		return (fatal("Colors failed"), free_element_walls(&data), 1);
	if (mlx_things(&data))
		return (fatal("MLX failed"), free_element_walls(&data), 1);
	return (free_all(&data), 0);
}
