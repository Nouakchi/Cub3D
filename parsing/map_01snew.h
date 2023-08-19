#ifndef MAP_01SNEW_H
# define MAP_01SNEW_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
void	*ft_calloc(size_t count, size_t size);
int		is_newline(char *s);
void	ft_error(char *msg, char *free_str1, char *free_str2);
void	ft_error_open(int fd);
char	**get_init_map(int fd);
#endif
