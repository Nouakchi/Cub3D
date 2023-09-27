/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 05:33:53 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"


int	main(int ac, char *av[])
{
	int		map_fd;
	t_data	data;

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
