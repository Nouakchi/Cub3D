/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_gotomlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:12:15 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/20 12:22:05 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


int init_mlx(t_data *data)
{
	void    *mlx_ptr;
	void    *win_ptr;
	int		width;
	int		height;
	int     i;
	int     j;

	int size;
	int x;
	int y;
	int ix;
	int jx;


	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	width = ft_strlen_width(data->map_data.map) * 50;
	height = ft_strlen_height(data->map_data.map) * 50;


	win_ptr = mlx_new_window(mlx_ptr, width, height, "Hello world!");
	if (!win_ptr)
		return (1);
	i = -1;


	size = 50;
	ix = 0;
	jx = 0;



	while (data->map_data.map[++i])
	{
		j = -1;
		while (data->map_data.map[i][++j])
		{
			if (data->map_data.map[i][j] == '1')
			{
				x = jx;
				while (x < size + jx)
				{
					y  = ix;
					while (y < size + ix)
					{
						if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x00FF0000) == -1)
							return (1);
						y++;
					}
					x++;
				}
				// while (x < size)
				// {
				// 	// red 0x00FF0000
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix + x, jx, 0x00FF0000) == -1)
				// 		return (1);
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix, jx + x, 0x00FF0000) == -1)
				// 		return (1);
				// 	x++;
				// }

			}
			else if (data->map_data.map[i][j] == 'N')
			{
				x = jx;
				while (x < size + jx)
				{
					y  = ix;
					while (y < size + ix)
					{
						if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
							return (1);
						y++;
					}
					x++;

				}

				// while (x < size)
				// {
				// 	// green 0x0000FF00
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix + x, jx, 0x0000FF00) == -1)
				// 		return (1);
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix, jx + x, 0x0000FF00) == -1)
				// 		return (1);
				// 	x++;
				// }
			}
			else if (data->map_data.map[i][j] == 'S')
			{
				x = jx;
				while (x < size + jx)
				{
					y  = ix;
					while (y < size + ix)
					{
						if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
							return (1);
						y++;
					}
					x++;

				}

				// while (x < size)
				// {
				// 	// green 0x0000FF00
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix + x, jx, 0x0000FF00) == -1)
				// 		return (1);
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix, jx + x, 0x0000FF00) == -1)
				// 		return (1);
				// 	x++;
				// }
			}
			else if (data->map_data.map[i][j] == 'E')
			{
				x = jx;
				while (x < size + jx)
				{
					y  = ix;
					while (y < size + ix)
					{
						if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
							return (1);
						y++;
					}
					x++;

				}

				// while (x < size)
				// {
				// 	// green 0x0000FF00
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix + x, jx, 0x0000FF00) == -1)
				// 		return (1);
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix, jx + x, 0x0000FF00) == -1)
				// 		return (1);
				// 	x++;
				// }
			}
			else if (data->map_data.map[i][j] == 'W')
			{
				x = jx;
				while (x < size + jx)
				{
					y  = ix;
					while (y < size + ix)
					{
						if (mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0000FF00) == -1)
							return (1);
						y++;
					}
					x++;

				}
				// while (x < size)
				// {
				// 	// green 0x0000FF00
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix + x, jx, 0x0000FF00) == -1)
				// 		return (1);
				// 	if (mlx_pixel_put(mlx_ptr, win_ptr, ix, jx + x, 0x0000FF00) == -1)
				// 		return (1);
				// 	x++;
				// }
			}
			jx += size;
		}
		jx = 0;
		ix += size;
	}
	mlx_loop(mlx_ptr);
	return (0);
}

int go_to_mlx(t_data *data)
{

	if (init_mlx(data))
		return (1);
	return (0);

}
