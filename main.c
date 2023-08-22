/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/21 16:38:55 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

void	fatal(char *mssg)
{
	printf("Error\n%s\n", mssg);
	exit(0);
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

int	main(int ac, char *av[])
{
	atexit(check);
	int		map_fd;
	t_data	data;
	int		i;

	if (ac != 2)
		return (fatal("Few arguments !!"), 1);
	if (ft_strlen(av[1]) < 5)
		return (fatal("The Extension not Valid"), 1);
	else
	{
		i = ft_strlen(av[1]) - 1;
		if (av[1][i] != 'b' || av[1][i - 1] != 'u' || av[1][i - 2] != 'c' || av[1][i - 3] != '.')
			ft_error("The Extension not Valid", NULL, NULL);
	}
	map_fd = open(av[1], O_RDONLY);
	if (map_fd == -1)
		return (fatal("Invalid file !!"), 0);
	data_init(&data);
	 if (!check_element(map_fd, &data))
        return (1); // free data and close
	// if (check_map_pars(map_fd, &data))
	// 	return (fatal("Invalid map"), 1); // free data // close map_fd

	// trim_map(&data);

// check when map not exist in .cub file


	if (close(map_fd) == -1)
		return (fatal("Error closing file !!"), 0); // free data

	free(data.map_data.map_elements.east_text);
	free(data.map_data.map_elements.west_text);
	free(data.map_data.map_elements.north_text);
	free(data.map_data.map_elements.south_text);
	
	// free_map(data.map_data.map);
	
	// if (go_to_mlx(&data))
	// 	return (1); // free data
	
	render(&data);

	return (0);

}
