#ifndef MAP_01SNEW_H
# define MAP_01SNEW_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_error(char *msg, char *free_str1, char *free_str2);
void	ft_error_open(int fd);
char	**get_init_map(int fd);
void	free_map(char **map);
char	*ft_strjoin_free(char *s1, char *s2);
int		check_map(char **map);
int		check_chars(char **map);
int		check_walls(char **map);
int		check_empty_lines(char **map);
int		check_order(char **map);
int		check_spaces(char **map);
int		ft_strlen_height(char **map);
int		ft_strlen_width(char **map);
char	**add_spaces(char **map);

#endif

