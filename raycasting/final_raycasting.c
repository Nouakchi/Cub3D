/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:32:02 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/24 14:18:23 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void draw_line(void *mlx_ptr, void *mlx_win, int x_start, int y_start, int y_end)
{
	while (y_start <= y_end)
		mlx_pixel_put(mlx_ptr, mlx_win, x_start, y_start++, 0x00FF0000);
}

int	render(t_data *data, double angle, void *mlx_ptr, void *mlx_win, int start)
{
    char map[5][6] = {
		{1,1,1,1,1,1},
		{1,0,0,1,0,1},
		{1,0,0,0,0,1},
		{1,0,0,0,9,1},
		{1,1,1,1,1,1},
	};
    
    double wall_height = 64.0;
	int wall_height_shift = log2(wall_height);
    
    double playr_x = 288;
	double playr_y = 224;
    
    // check horizontal intersection
    
    double first_horz_inter_y = ((int)floor((int)playr_y >> wall_height_shift) << wall_height_shift) - 1;;
    double first_horz_inter_x = playr_x + (playr_y - first_horz_inter_y) / tan(angle * (M_PI / 180.0));
    
    double Xa = 64 / tan(angle * (M_PI / 180.0));
    double Ya = -64;
    

    int i = (int)first_horz_inter_y  >> wall_height_shift;
	int j = (int)first_horz_inter_x  >> wall_height_shift;
    
    while (i < 5 && i >= 0 && j < 6 && j >= 0 && map[i][j] != 1)
	{
		first_horz_inter_y += Ya;
		first_horz_inter_x += Xa;
		i = (int)first_horz_inter_y >> wall_height_shift;
		j = (int)first_horz_inter_x >> wall_height_shift;
	}
	
    // check vertical
    
    Xa = 64;
    Ya = 64 * tan(angle * (M_PI / 180.0));
	
	if (angle >= 90)
		Xa *= -1;
    double tmp = (angle < 90) ? 64 : 0;
    double first_vert_inter_x = ((int)floor((int)playr_x >> wall_height_shift) << wall_height_shift) + tmp;
	double first_vert_inter_y = playr_y - ((first_vert_inter_x - playr_x) * tan(angle * (M_PI / 180.0)));

    
    i = (int)first_vert_inter_y  >> wall_height_shift;
	j = (int)first_vert_inter_x  >> wall_height_shift;
	
	if (angle >= 90)
		j--;


    while (i < 5 && i >= 0 && j < 6 && j >= 0 && map[i][j] != 1)
	{
		if (angle < 90 )
			first_vert_inter_y -= Ya;
		else
			first_vert_inter_y += Ya;
		first_vert_inter_x += Xa;
		
		i = (int)first_vert_inter_y >> wall_height_shift;
		j = (int)first_vert_inter_x >> wall_height_shift;
		if (angle >= 90)
			j--;
	}
	

	double horz_dist = (double)fabs(playr_y - first_horz_inter_y) / sin(angle * (M_PI / 180.0));
	double vert_dist = (double)fabs(playr_y - first_vert_inter_y) / sin(angle * (M_PI / 180.0));
	
	double ray = horz_dist;
	if (ray > vert_dist)
		ray = vert_dist;
	
	//
	double beta_angle = angle - 90;
	
	ray = (double)ray * cos(beta_angle * (M_PI / 180.0));
	//886.8100134753
	double actual_height = ceil((64 * 886) / ray);
	
	draw_line(mlx_ptr, mlx_win, start, (256 - (actual_height / 2)), (256 - (actual_height / 2)) + actual_height);



    // getchar();
    (void) data, (void)mlx_ptr, (void)mlx_win, (void)start;
    return (0);
}