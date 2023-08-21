/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_gotomlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:12:15 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/21 11:52:13 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

#define PI 3.14159265359


int ft_loop_hook(void *param)
{
	(void)param;
	printf("loop_hook\n");
	return (0);
}

int ft_key_hook(int keycode, void *param)
{
	(void)param;
	printf("key_hook\n");
	printf("keycode: %d\n", keycode);
	return (0);
}


int	init_mlx(t_data *data)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	int		i;
	int		j;
	int		size_x;
	int		size_y;
	int		x;
	int		y;
	int		ix;
	int		jx;
	int x_tail;
	int cordinates[2];

	i = -1;
	ix = 0;
	jx = 0;
	x_tail = 0;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);

	width = 2800; // 400
	height = 1500; // 400
	size_x = (width / 3) / ft_strlen_width(data->map_data.map);
	size_y = (height / 3) / ft_strlen_height(data->map_data.map);
	win_ptr = mlx_new_window(mlx_ptr, width, height, "Hello world!");
	if (!win_ptr)
		return (1);

	while (data->map_data.map[++i])
	{
		j = -1;
		while (data->map_data.map[i][++j])
		{
			cordinates[0] = (jx - 1) + (size_x / 2);
			cordinates[1] = (ix - 1) + (size_y / 2);
			x = jx - 1;
			if (data->map_data.map[i][j] == '1')
			{
				while (++x < size_x + jx)
				{
					y = ix - 1;
					while (++y < size_y + ix)
						if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x00FF0000) == -1)
							return (1);
				}
			}
			else if (data->map_data.map[i][j] == 'N')
			{
				// N = North
				while (++x < size_x + jx)
				{
					y = ix - 1;
					while (++y < size_y + ix)
					{
						if (sqrt(pow(x - cordinates[0], 2) + pow(y - cordinates[1], 2)) <= size_x / 4)
							if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
								return (1);
					}
				}
				x = cordinates[0];
				while (++x < size_x + jx)
				{
					if (mlx_pixel_put(mlx_ptr, win_ptr, x, cordinates[1], 0x0000FF00) == -1)
						return (1);
				}
			}
			else if (data->map_data.map[i][j] == 'S')
			{
				while (++x < size_x + jx)
				{
					y = ix - 1;
					while (++y < size_y + ix)
					{
						if (sqrt(pow(x - cordinates[0], 2) + pow(y - cordinates[1], 2)) <= size_x / 4)
							if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
								return (1);
					}
				}
				x = cordinates[0];
				while (++x < size_x + jx)
				{
					if (mlx_pixel_put(mlx_ptr, win_ptr, x, cordinates[1], 0x0000FF00) == -1)
						return (1);
				}
			}
			else if (data->map_data.map[i][j] == 'E')
			{
				// E = East
				while (++x < size_x + jx)
				{
					y = ix - 1;
					while (++y < size_y + ix)
					{
						if (sqrt(pow(x - cordinates[0], 2) + pow(y - cordinates[1], 2)) <= size_x / 4)
							if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
								return (1);
					}
				}
				x = cordinates[0];
				while (++x < size_x + jx)
				{
					if (mlx_pixel_put(mlx_ptr, win_ptr, x, cordinates[1], 0x0000FF00) == -1)
						return (1);
				}
			}
			else if (data->map_data.map[i][j] == 'W')
			{
				// W = West
				while (++x < size_x + jx)
				{
					y = ix - 1;
					while (++y < size_y + ix)
					{
						if (sqrt(pow(x - cordinates[0], 2) + pow(y - cordinates[1], 2)) <= size_x / 4)
							if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
								return (1);
					}
				}
				x = cordinates[0];
				while (--x > jx - 1)
				{
					if (mlx_pixel_put(mlx_ptr, win_ptr, x, cordinates[1], 0x0000FF00) == -1)
						return (1);
				}
			}
			jx += size_x;
		}
		jx = 0;
		ix += size_y;
	}
	// add loop hook
	// if (mlx_loop_hook(mlx_ptr, ft_loop_hook, NULL) == -1)
	// 	return (1);


	if (mlx_hook(win_ptr, 2, 1L<<0, ft_key_hook, NULL) == -1)
		return (1);

	mlx_loop(mlx_ptr);
	return (0);
}

int	go_to_mlx(t_data *data)
{
	if (init_mlx(data))
		return (1);
	return (0);
}
