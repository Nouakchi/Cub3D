/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:46:21 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 17:04:34 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_main.h"

void	tt(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*init_map;
	char	**map;

	if (argc != 2)
		ft_error("Error\nMore or Less tha 2 args", NULL, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error\nOpen Error", NULL, NULL);
	init_map = get_init_map(fd);
	init_map = ft_strtrim(init_map, "\n");
	if (check_init_map(init_map))
		ft_error("Error\nMap Error", init_map, NULL);
	map = ft_split(init_map, '\n');
	if (!map)
		ft_error("Error\nMalloc Error", init_map, NULL);


	// int i = -1;
	// while (map[++i])
	// 	printf("%s\n", map[i]);


	free(init_map);
	if (check_map(map))
		ft_error("Error\nMap Error", NULL, NULL);
	if (close(fd) == -1)
		ft_error("Error\nClose Error", NULL, NULL);
	return (0);
}
