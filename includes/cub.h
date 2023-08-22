/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:12:48 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/22 14:33:27 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _CUB_H_
# define _CUB_H_

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;

typedef struct s_map_elements
{
    char *north_text;
    char *south_text;
    char *west_text;
    char *east_text;
    t_rgb frgb;
    t_rgb crgb;
} t_map_elements;

typedef struct s_map
{
    t_map_elements  map_elements;
    char            **map;
}   t_map;

typedef struct s_data
{
    t_map map_data;
}   t_data;


int     check_element(int map, t_data *data);
void    fatal(char *mssg);
void	ft_error(char *msg, char *free_str1, char *free_str2);
char	*get_init_map(int fd);
void	free_map(char **map);
char	*ft_strjoin_free(char *s1, char *s2);
int		check_map(char **map);
int		check_init_map(char *map);
int		check_chars(char *map);
int		check_walls(char **map);
int		ft_strlen_height(char **map);
int		ft_strlen_width(char **map);
int		check_walls_utils(char **map, int i, int j);
int		check_chars_utils(char map);
int		check_newline(char *map);
int     check_map_pars(int map_fd, t_data *data);
int     is_numeric(char *str);
int	    count_commas(char *str);
int	    parse_rgb(char *rgb_str, t_rgb *rgb);
char	*remove_newline(char *line);
int     read_line(int map, char **line);
int	    parse_element(char *identifier, char *path_rgb, t_data *data, int *all_in);
int go_to_mlx(t_data *data);
void    trim_map(t_data *data);
int join_nulls(t_data *data);
# endif
