#include "map_01snew.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	**map;

	if (argc != 2)
		ft_error("Error\nMore or Less tha 2 args", NULL, NULL);

	// check .cub extension

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error\nOpen Error", NULL, NULL);

	map = get_init_map(fd);

	// check map is valid

	return (0);
}
