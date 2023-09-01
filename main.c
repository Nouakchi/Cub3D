/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/01 15:53:51 by onouakch         ###   ########.fr       */
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

// void check()
// {
// 	system("leaks cub3D");
// }

int	main(int ac, char *av[])
{
	// atexit(check);
	int		map_fd;
	t_data	data;
	int		i;

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
			}
		}
		if (data.map_data.map_width < (int)ft_strlen(data.map_data.map[i]))
			data.map_data.map_width = (int)ft_strlen(data.map_data.map[i]);
	}
	data.map_data.map_height = i;

	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, 1024, 512, "cub3D");

	// do raycasting here
	data.ray.angle = 120;
	data.player.view_angle = data.ray.angle - 30;

	mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_hook(data.mlx_win, 2,0, moves, &data);
	
	mlx_loop(data.mlx_ptr);
	
	free_element_map(&data);



	return (0);

}
