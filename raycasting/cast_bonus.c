/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:31:37 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/26 07:14:13 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/cub.h"

int     check_exit(t_data *data, double *pos_x, double *pos_y)
{
    if ((data->player.view_angle >= 0 && data->player.view_angle <= 90) || (data->player.view_angle > 180 && data->player.view_angle <= 270))
            if (data->map_data.map[(int)(*pos_y + 8) >> (int)WALL_SHIFT][(int)(*pos_x + 8) >> (int)WALL_SHIFT] == '1'
            && data->map_data.map[(int)(*pos_y - 8) >> (int)WALL_SHIFT][(int)(*pos_x - 8) >> (int)WALL_SHIFT] == '1')
                return (1);
    if ((data->player.view_angle > 90 && data->player.view_angle <= 180) || (data->player.view_angle > 270 && data->player.view_angle <= 360))
        if (data->map_data.map[(int)(*pos_y - 8) >> (int)WALL_SHIFT][(int)(*pos_x + 8) >> (int)WALL_SHIFT] == '1'
        && data->map_data.map[(int)(*pos_y + 8) >> (int)WALL_SHIFT][(int)(*pos_x - 8) >> (int)WALL_SHIFT] == '1')
            return (1);
    return (0);
}

void    move_forward(t_data *data, double *pos_x, double *pos_y)
{
    double next_pos_x;
    double next_pos_y;
    *pos_x += SPEED * cos(data->player.view_angle * (M_PI / 180));
    if (data->player.view_angle >= 180)
        *pos_y += SPEED * fabs(sin(data->player.view_angle * (M_PI / 180)));
    else
        *pos_y -= SPEED * sin(data->player.view_angle * (M_PI / 180));
    next_pos_x = data->player.x_pos;
    next_pos_y = data->player.y_pos;
    if (data->map_data.map[(int)(*pos_y) >> (int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
    {
        if (check_exit(data, pos_x, pos_y))
            return ;
        data->player.x_pos = *pos_x;
        data->player.y_pos = *pos_y;
    }
}

void    move_backward(t_data *data, double *pos_x, double *pos_y)
{
   if (data->player.view_angle <= 90 || data->player.view_angle >= 270)
        *pos_x -= SPEED * cos(data->player.view_angle * (M_PI / 180));
    else
        *pos_x += SPEED * fabs(cos(data->player.view_angle * (M_PI / 180)));
    *pos_y += SPEED * sin(data->player.view_angle * (M_PI / 180));
    if (data->map_data.map[(int)(*pos_y) >> (int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
    {
        data->player.x_pos = *pos_x;
        data->player.y_pos = *pos_y;
    }
}

void    move_right(t_data *data, double *pos_x, double *pos_y)
{
    double  righ_view_angle;
    
    righ_view_angle = data->player.view_angle - 90;
    if (righ_view_angle < 0)
        righ_view_angle = 360 + (data->player.view_angle - 90);
    *pos_x += SPEED * cos(righ_view_angle * (M_PI / 180));
    if (righ_view_angle >= 180)
        *pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
    else
        *pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
    if (data->map_data.map[(int)(*pos_y) >> (int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
    {
        if (check_exit(data, pos_x, pos_y))
            return ;
        data->player.x_pos = *pos_x;
        data->player.y_pos = *pos_y;
    }
}

void    move_left(t_data *data, double *pos_x, double *pos_y)
{
    double  righ_view_angle;
    
    righ_view_angle = data->player.view_angle + 90;
    if (righ_view_angle >= 360)
        righ_view_angle = fabs(360 - (data->player.view_angle + 90));
    *pos_x += SPEED * cos(righ_view_angle * (M_PI / 180));
    if (righ_view_angle >= 180)
        *pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
    else
        *pos_y -= SPEED * sin(righ_view_angle * (M_PI / 180));
    if (data->map_data.map[(int)(*pos_y) >> (int)WALL_SHIFT][(int)(*pos_x) >> (int)WALL_SHIFT] != '1')
    {
        if (check_exit(data, pos_x, pos_y))
            return ;
        data->player.x_pos = *pos_x;
        data->player.y_pos = *pos_y;
    }
}

void    rotate_right(t_data *data)
{
    if (data->ray.angle - (ROTATION * DIFF_RAYS) <= 0)
        data->ray.angle = 360 + (data->ray.angle - (ROTATION * DIFF_RAYS));
    else
        data->ray.angle -= (ROTATION * DIFF_RAYS);
    if (data->ray.angle <= (FOV / 2))
        data->player.view_angle = 360 - ((FOV / 2) - data->ray.angle);
    else
        data->player.view_angle = data->ray.angle - (FOV / 2);
}

void    rotate_left(t_data *data)
{
    if (data->ray.angle + (ROTATION * DIFF_RAYS) >= 360)
        data->ray.angle = fabs(360 - (data->ray.angle + (ROTATION * DIFF_RAYS)));
    else
        data->ray.angle += (ROTATION * DIFF_RAYS);
    if (data->ray.angle <= (FOV / 2))
        data->player.view_angle = 360 - ((FOV / 2) - data->ray.angle);
    else
        data->player.view_angle = data->ray.angle - (FOV / 2);
}

void update_data(t_data *data)
{

    double pos_x = data->player.x_pos;
    double pos_y = data->player.y_pos;
    
    if (data->moves.move_f)
        move_forward(data, &pos_x, &pos_y);
    if (data->moves.move_b)
        move_backward(data, &pos_x, &pos_y);
    if (data->moves.move_r)
        move_right(data, &pos_x, &pos_y);
    if (data->moves.move_l)
        move_left(data, &pos_x, &pos_y);
    if (data->moves.rotate_r)
        rotate_right(data);
    if (data->moves.rotate_l)
        rotate_left(data);
}
void    cast_rays(t_data *data)
{
    int     start;
    double  beta_angle;

    start = -1;
	beta_angle = (FOV / 2);
    while (start < W_WIDTH - 1)
	{
		if (data->ray.angle > 180 && data->ray.angle < 360)
			down_cast(data, ++start, beta_angle);
		else
			up_cast(data, ++start, beta_angle);
		if (data->ray.angle <= 0)
			data->ray.angle = 360 - DIFF_RAYS;
		else
			data->ray.angle -= DIFF_RAYS;
		beta_angle -= DIFF_RAYS;
	}
}

int mouse_hook(t_data *data)
{
    int x;
    int y;

    if (!data->mouse_app)
    {
        if (mlx_mouse_get_pos(data->mlx_win, &x, &y) == -1)
        {
            printf("error\n"); // TODO: handle error
            exit(1);
        }
        if (x != W_WIDTH / 2)
        {
            if (x > W_WIDTH / 2)
                rotate_right(data);
            else
                rotate_left(data);
        }
        if (mlx_mouse_move(data->mlx_win, W_WIDTH / 2, W_HEIGHT / 2) == -1)
        {
            printf("error\n"); // TODO: handle error
            exit(1);
        }
    }
    return (0);
}

void draw_mini_cube(t_data *data, int x, int y, unsigned int color)
{
    int i;
    int j;

    i = x - 6;
    while (++i < x + 6)
    {
        j = y - 6;
        while (++j < y + 6)
            my_mlx_pixel_put(&data->img, j, i, color);
    }
}

void    mini_map(t_data *data)
{
    int start_x;
    int start_y;
    int map_x;
    int map_y;
    unsigned color;
    unsigned color_;
    int i;
    int j;
    
    start_y = -1;
    map_y = data->player.y_pos - 125;
    color = (255 * pow(2,16)) + (255 * pow(2,8)) + 255;
    color_ = (255 * pow(2,16)) + (0 * pow(2,8)) + 0;
    while(++start_y < 250)
    {
        start_x = -1;
        map_x = data->player.x_pos - 125;
        while (++start_x < 250)
        {
            i = (int)map_y  >> (int)WALL_SHIFT;
	        j = (int)map_x >> (int)WALL_SHIFT;
            if (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width  && j >= 0 && data->map_data.map[i][j] == '1')
                my_mlx_pixel_put(&data->img, start_x, start_y, color);
            else if (i < data->map_data.map_height && i >= 0 && j < data->map_data.map_width  && j >= 0 && data->map_data.map[i][j] == '0')
                my_mlx_pixel_put(&data->img, start_x, start_y, 0);
            else
                my_mlx_pixel_put(&data->img, start_x, start_y, color_);
            map_x++;
        }
        map_y++;
    }
    draw_mini_cube(data, 125, 125, color_);
}

int render(void *args)
{
    t_data *data;
    double  angle;

    data = args;
    update_data(data);
    mouse_hook(data);
    angle = data->ray.angle;
    data->img.img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
    if (!data->img.img)
    {
        printf("error\n"); // TODO: handle error
        exit(1);
    }
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
    &data->img.line_length, &data->img.endian);
    if (!data->img.addr)
    {
        printf("error\n"); // TODO: handle error
        exit(1);
    }
    cast_rays(data);
    mini_map(data);
    data->ray.angle = angle;
    if (mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0) == -1)
    {
        printf("error\n"); // TODO: handle error
        exit(1);
    }
    if (mlx_destroy_image(data->mlx_ptr, data->img.img) == -1)
    {
        printf("error\n"); // TODO: handle error
        exit(1);
    }
    return (0);
}

int moves_press(int keycode, void *args)
{
    t_data *data;

    data = args;
    if (keycode == RIGHT_KEY)
        data->moves.move_r = 1;
    else if (keycode == LEFT_KEY)
        data->moves.move_l = 1;
    else if (keycode == UP_KEY)
        data->moves.move_f = 1;
    else if (keycode == DOWN_KEY)
        data->moves.move_b = 1;
    else if (keycode == QUIT_KEY)
    {
        free_element_map(data);
        exit(1);
    }
    else if (keycode == ROTATE_L) // left
        data->moves.rotate_l = 1;
    else if (keycode == ROTATE_R) // right
        data->moves.rotate_r = 1;
    else if (keycode == 49)
    {
        data->mouse_app = !data->mouse_app;
        if (!data->mouse_app)
        {
            if (mlx_mouse_hide() == -1)
            {
                printf("error\n"); // TODO: handle error
                exit(1);
            }
        }
        else
        {
            if (mlx_mouse_show() == -1)
            {
                printf("error\n"); // TODO: handle error
                exit(1);
            }
        }
    }
    return (0);
}

int moves_release(int keycode, void *args)
{
    t_data *data;

    data = args;
    if (keycode == RIGHT_KEY)
        data->moves.move_r = 0;
    else if (keycode == LEFT_KEY)
        data->moves.move_l = 0;
    else if (keycode == UP_KEY)
        data->moves.move_f = 0;
    else if (keycode == DOWN_KEY)
        data->moves.move_b = 0;
    if (keycode == ROTATE_R)
        data->moves.rotate_r = 0;
    else if (keycode == ROTATE_L)
        data->moves.rotate_l = 0;
    return (0);
}

void    mouse_visibility(t_data *data)
{
    data->mouse_app = 0;
	if (mlx_mouse_hide() == -1)
	{
		printf("error\n"); // TODO: handle error
		exit(1);
	}
}