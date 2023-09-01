/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:12:48 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/01 16:24:10 by onouakch         ###   ########.fr       */
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
# include <math.h>

# define WALL_HEIGHT 64.0
# define WALL_SHIFT log2(64.0)

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
    int             map_height;
    int             map_width;
}   t_map;

typedef struct s_player_data
{
    double  x_pos;
    double  y_pos;
    double  view_angle;
    double  distance_to_wall;
    
}   t_player_data;

typedef struct s_ray
{
    double  angle;
    double  x_step;
    double  y_step;
    double  x_inter;
    double  y_inter;
    
}   t_ray;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_moves
{
    int move_f;
    int move_b;
    int move_l;
    int move_r;
}   t_moves;

typedef struct s_data
{
    t_map           map_data;
    t_player_data   player;
    void            *mlx_ptr;
	void            *mlx_win;
    t_ray           ray;
    t_img           img;
    t_moves         moves;
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
int     go_to_mlx(t_data *data);
void    trim_map(t_data *data);
int     join_nulls(t_data *data);
int	    down_cast(t_data *data, int start, double beta_angle);
int	    up_cast(t_data *data, int start, double beta_angle);
void    draw_line(t_data *data, int x_start, int y_start, int y_end);
int     render(void *data);
int     moves_press(int keycode, void *args);
int     moves_release(int keycode, void *args);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

# endif
