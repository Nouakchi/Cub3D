/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:12:48 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 07:43:00 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB_H_
# define _CUB_H_

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>

# define WALL_HEIGHT 64.0
# define FOV 60.0
# define W_WIDTH 1024.0
# define W_HEIGHT 512.0
# define SPEED 4.0
# define ROTATION 35.0
# define WALL_SHIFT log2(64.0)
# define DIFF_RAYS FOV / W_WIDTH
# define DIST_TO_PROJ (W_WIDTH / 2) / tan((FOV / 2) * (M_PI / 180.0))
# define RIGHT_KEY 2
# define LEFT_KEY 0
# define UP_KEY 13
# define ROTATE_R 124
# define ROTATE_L 123
# define DOWN_KEY 1
# define QUIT_KEY 53


typedef struct s_mini_map
{
	int				start_x;
	int				start_y;
	int				map_x;
	int				map_y;
	int				i;
	int				j;
	unsigned int	color;
	unsigned int	color_;
}					t_mini_map;

typedef struct s_cond
{
	int				x_start;
	int				y_start;
	int				y_end;
	double			ac_h;
}					t_cond;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_rgbt
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	t;
}					t_rgbt;

typedef struct s_map_elements
{
	char			*north_text;
	char			*south_text;
	char			*west_text;
	char			*east_text;

	unsigned int	**colors_north;
	unsigned int	**colors_south;
	unsigned int	**colors_west;
	unsigned int	**colors_east;

	t_rgb			frgb;
	t_rgb			crgb;
}					t_map_elements;

typedef struct s_map
{
	t_map_elements	map_elements;
	char			**map;
	int				map_height;
	int				map_width;
}					t_map;

typedef struct s_player_data
{
	double			x_pos;
	double			y_pos;
	double			view_angle;
	double			distance_to_wall;
	char			start_angle;

}					t_player_data;

typedef struct s_ray
{
	double			angle;
	double			x_step;
	double			y_step;
	double			x_h_inter;
	double			y_h_inter;
	double			x_v_inter;
	double			y_v_inter;
	double			x_inter;
	double			y_inter;
	int				is_vert;

}					t_ray;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_moves
{
	int				move_f;
	int				move_b;
	int				move_l;
	int				move_r;
	int				rotate_l;
	int				rotate_r;
}					t_moves;

typedef struct s_mouse
{
    int x;
    int y;
}   t_mouse;

typedef struct s_data
{
	t_map			map_data;
	t_player_data	player;
	double			last_ray;
	double			last_x_inter;
	double			last_y_inter;
	void			*mlx_ptr;
	void			*mlx_win;
	t_ray			ray;
	t_img			img;
	t_img			img_north;
	t_img			img_south;
	t_img			img_west;
	t_img			img_east;
	t_moves			moves;
	int				mouse_app;
}					t_data;

int					render(void *args);
void				mini_map(t_data *data);
int					mouse_hook(t_data *data);
void				update_data(t_data *data);
int					mouse_visibility(t_data *data);
int					moves_press(int keycode, void *args);
int					moves_release(int keycode, void *args);
void				rotate_right(t_data *data);
void				rotate_left(t_data *data);
int					init_colors(t_data *data);
void				free_color(unsigned int **color);
void				fatal(char *mssg);
void				free_element_(t_data *data);
void				free_element(t_data *data, int map_fd);
void				free_element_walls(t_data *data);
void 				free_all(t_data *data);
int 				free_all_success(t_data *data);
void				free_all_fatal(char *msg ,t_data *data);
void				free_map(char **map);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				destroy_image_1(t_data *data);
void				destroy_image_2(t_data *data);
void				destroy_image_3(t_data *data);
void				destroy_image_4(t_data *data);
int					init_textures(t_data *data, int size);
int					init_my_mlx(t_data *data);
int					parse_rgb(char *rgb_str, t_rgb *rgb);
int					read_line(int map, char **line);
int					check_element(int map, t_data *data);
int					check_walls_utils(char **map, int i, int j);
int					check_init_map(char *map);
int					check_map(char **map);
int					check_map_pars(int map_fd, t_data *data);
int					check_chars(char *map);
int					check_walls(char **map);
char				*get_init_map(int fd);
int					check_newline(char *map);
int					check_map_is_valid(int map_fd, t_data *data);
void				trim_map(t_data *data);
int					join_nulls(t_data *data);
int					check_extension(int ac, char *av[]);
int					down_cast(t_data *data, int start, double beta_angle);
int					up_cast(t_data *data, int start, double beta_angle);
void				check_0_degrees(t_data *data, double *ray);
int					check_exit(t_data *data, double *pos_x, double *pos_y);
void				data_map_init(t_data *data);
void				init_player_map(t_data *data);
void				init_angles_moves(t_data *data);
int 				free_all_success(t_data *data);
int					mlx_things(t_data *data);
int					ft_strlen_width(char **map);
int					ft_strlen_height(char **map);
void				draw_line(t_data *data, t_cond c);
void				free_element_mlx(t_data *data);


#endif
