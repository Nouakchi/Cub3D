/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:12:48 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/22 06:02:50 by onouakch         ###   ########.fr       */
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
# define FOV 60.0
# define W_WIDTH 1024.0
# define W_HEIGHT 512.0
# define SPEED 8.0
# define ROTATION 35.0
# define WALL_SHIFT log2(64.0)
# define DIFF_RAYS FOV / W_WIDTH
# define DIST_TO_PROJ (W_WIDTH / 2) / tan((FOV / 2) * (M_PI / 180.0))
# define RIGHT_KEY 2
# define LEFT_KEY 0
# define UP_KEY 13
# define DOWN_KEY 1
# define QUIT_KEY 53

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

    unsigned int **colors_north;
    unsigned int **colors_south;
    unsigned int **colors_west;
    unsigned int **colors_east;

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
    char    start_angle;

}   t_player_data;

typedef struct s_ray
{
    double  angle;
    double  x_step;
    double  y_step;
    double  x_h_inter;
    double  y_h_inter;
    double  x_v_inter;
    double  y_v_inter;
    double  x_inter;
    double  y_inter;
    int     is_vert;

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
    double          last_ray;
    double          last_x_inter;
    double          last_y_inter;
    void            *mlx_ptr;
	void            *mlx_win;
    t_ray           ray;
    t_img           img;
    t_img           img_north; //
    t_img           img_south;
    t_img           img_west;
    t_img           img_east;
    t_moves         moves;
    int             mouse_app;
}   t_data;

void	free_element_map(t_data *data);
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
void    draw_line(t_data *data, int x_start, int y_start, int y_end, int actual_height);
int     render(void *data);
int     moves_press(int keycode, void *args);
int     moves_release(int keycode, void *args);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

# endif
