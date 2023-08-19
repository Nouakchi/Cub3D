/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_map_01snew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:46:21 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 11:08:35 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_map_01snew.h"

void	tt(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	// atexit(tt);
	int		fd;
	char	**map;
	char	**map2;
	char	**map3;

	if (argc != 2)
		ft_error("Error\nMore or Less tha 2 args", NULL, NULL);

	// check .cub extension

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error\nOpen Error", NULL, NULL);

	map = get_init_map(fd);

	// if (check_map_1(map))
	// 	ft_error("Error\nMap Error", NULL, NULL);
	// map2 = get_init_map_2(map);
	// free_map(map);

	map3 = add_spaces(map);

	int i = -1;
	while (map3[++i])
		printf("%s\n", map3[i]);


	// if (check_map(map3))
	// 	ft_error("Error\nMap Error", NULL, NULL);

	// free_map(map3);

	// if (close(fd) == -1)
	// 	ft_error("Error\nClose Error", NULL, NULL);

	return (0);
}
