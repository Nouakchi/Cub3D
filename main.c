/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/26 08:13:49 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	fatal(char *mssg)
{
	write(2, "Error\n", 6);
	write(2, mssg, ft_strlen(mssg));
	write(2, "\n", 1);
}

void	fatal_free_element(char *mssg, t_data *data, int map_fd)
{
	write(2, "Error\n", 6);
	write(2, mssg, ft_strlen(mssg));
	write(2, "\n", 1);
	free(data->map_data.map_elements.east_text);
	free(data->map_data.map_elements.west_text);
	free(data->map_data.map_elements.north_text);
	free(data->map_data.map_elements.south_text);
	if (close(map_fd) == -1)
		fatal("Close failed");
}

void	free_element_map(t_data *data)
{
	free(data->map_data.map_elements.east_text);
	free(data->map_data.map_elements.west_text);
	free(data->map_data.map_elements.north_text);
	free(data->map_data.map_elements.south_text);
	free_map(data->map_data.map);
}

void	data_init(t_data *data)
{
	data->map_data.map_elements.east_text = NULL;
	data->map_data.map_elements.west_text = NULL;
	data->map_data.map_elements.north_text = NULL;
	data->map_data.map_elements.south_text = NULL;
	data->map_data.map = NULL;
	data->map_data.map_elements.frgb.r = -1;
	data->map_data.map_elements.crgb.r = -1;
}

void check()
{
	system("leaks cub3D");
}



void init_textures(t_data *data)
{
	int size = 64;
	data->img_north.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map_data.map_elements.north_text, &size, &size);
	if (!data->img_north.img)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	data->img_north.addr = mlx_get_data_addr(data->img_north.img, &data->img_north.bits_per_pixel, &data->img_north.line_length,
							&data->img_north.endian);
	if (!data->img_north.addr)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}

	data->img_south.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map_data.map_elements.south_text, &size, &size);
	if (!data->img_south.img)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	data->img_south.addr = mlx_get_data_addr(data->img_south.img, &data->img_south.bits_per_pixel, &data->img_south.line_length,
							&data->img_south.endian);
	if (!data->img_south.addr)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}

	data->img_east.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map_data.map_elements.east_text, &size, &size);
	if (!data->img_east.img)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	data->img_east.addr = mlx_get_data_addr(data->img_east.img, &data->img_east.bits_per_pixel, &data->img_east.line_length,
							&data->img_east.endian);
	if (!data->img_east.addr)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}


	data->img_west.img = mlx_xpm_file_to_image(data->mlx_ptr, data->map_data.map_elements.west_text, &size, &size);
	if (!data->img_west.img)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	data->img_west.addr = mlx_get_data_addr(data->img_west.img, &data->img_west.bits_per_pixel, &data->img_west.line_length,
							&data->img_west.endian);
	if (!data->img_west.addr)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}

}

unsigned int **get_color_each_pixel_from_img(t_img *img)
{
	int i = 0;
	int j = 0;
	// int index = 0;
	unsigned int color_r;
	unsigned int color_g;
	unsigned int color_b;
	unsigned int color_t;
	unsigned int color;
	unsigned int **map;

	map = malloc(sizeof(unsigned int *) * 64);
	while (i < 64)
	{
		map[i] = malloc(sizeof(unsigned int) * 64);
		j = 0;
		while (j < 64)
		{
			color_t = (unsigned char)img->addr[(i * img->line_length + j * (img->bits_per_pixel / 8)) + 3];
			color_r = (unsigned char)img->addr[(i * img->line_length + j * (img->bits_per_pixel / 8)) + 2];
			color_g = (unsigned char)img->addr[(i * img->line_length + j * (img->bits_per_pixel / 8)) + 1];
			color_b = (unsigned char)img->addr[(i * img->line_length + j * (img->bits_per_pixel / 8))];
			color = (color_t << 24) | color_r << 16 | color_g << 8 | color_b;
			map[i][j] = color;
			j++;
		}
		i++;
	}
	return (map);
}

void hh ()
{
	system("leaks cub3D_bonus");
}

int	main(int ac, char *av[])
{
	int		map_fd;
	t_data	data;
	int		i;

	atexit(hh);
	if (ac != 2)
		return (fatal("Invalid Input"), 1);

	if (ft_strlen(av[1]) < 5)
		return (fatal("Invalid Input"), 1);
	else
	{
		i = ft_strlen(av[1]) - 1;
		if (av[1][i] != 'b' || av[1][i - 1] != 'u' || av[1][i - 2] != 'c' || av[1][i - 3] != '.')
			return (fatal("Invalid Input"), 1);
	}

	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
		return (fatal("Invalid Input"), 1);


	data_init(&data);

	 if (!check_element(map_fd, &data))
		return(fatal_free_element("Invalid Input", &data, map_fd), 1);

	if (check_map_pars(map_fd, &data))
		return(fatal_free_element("Invalid Input", &data, map_fd), 1);

	trim_map(&data);

	if (close(map_fd) == -1)
		fatal("Close failed");

	i = -1;
	data.map_data.map_width = 0;
	while (data.map_data.map[++i])
	{
		int j = -1;
		while (data.map_data.map[i][++j])
		{
			if (ft_strchr("NWSE", data.map_data.map[i][j]))
			{
				data.player.y_pos = i * 64 + 32;
				data.player.x_pos = j * 64 + 32;
				data.player.start_angle = data.map_data.map[i][j];
				data.map_data.map[i][j] = '0';
			}
		}
		if (data.map_data.map_width < (int)ft_strlen(data.map_data.map[i]))
			data.map_data.map_width = (int)ft_strlen(data.map_data.map[i]);
	}
	data.map_data.map_height = i;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	data.mlx_win = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
	if (!data.mlx_win)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}

	// do raycasting here
	if (data.player.start_angle == 'N')
		data.ray.angle = 120;
	else if (data.player.start_angle == 'W')
		data.ray.angle = 210;
	else if (data.player.start_angle == 'S')
		data.ray.angle = 300;
	else
		data.ray.angle = 30;
	data.player.view_angle = data.ray.angle - 30;
	data.moves.move_r = 0;
    data.moves.move_l = 0;
    data.moves.move_f = 0;
    data.moves.move_b = 0;
	
	init_textures(&data);
	
	/////


	data.map_data.map_elements.colors_north = get_color_each_pixel_from_img(&data.img_north);
	data.map_data.map_elements.colors_south = get_color_each_pixel_from_img(&data.img_south);
	data.map_data.map_elements.colors_east = get_color_each_pixel_from_img(&data.img_east);
	data.map_data.map_elements.colors_west = get_color_each_pixel_from_img(&data.img_west);
	
	mouse_visibility(&data);

	if (mlx_loop_hook(data.mlx_ptr, render, &data) == -1)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	if (mlx_hook(data.mlx_win, 2,0, moves_press, &data) == -1)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
	if (mlx_hook(data.mlx_win, 3,0, moves_release, &data) == -1)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}

	if (mlx_loop(data.mlx_ptr) == -1)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}

	free_element_map(&data);
}
