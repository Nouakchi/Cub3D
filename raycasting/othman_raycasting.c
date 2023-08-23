/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othman_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/23 16:48:28 by onouakch         ###   ########.fr       */
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
	
	char map[5][5] = {
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,0,0,9,1},
		{1,1,1,1,1},
	};
	
	//
	// int player_height = 32;
	double wall_height = 64.0;
	int wall_height_shift = log2(wall_height);
	
	// int FOV = 60;
	// int proj_plan_width = 320;
	// int proj_plan_height = 200;
	// int dist_plyr_to_projplan = (proj_plan_width / 2) / tan((FOV / 2.0) * (M_PI / 180.0));
		
	// int dimension_proj_plan = proj_plan_width * proj_plan_height;
		
	// int center_proj_plan_x = proj_plan_width / 2;
	// int center_proj_plan_y = proj_plan_height / 2;

	// float angle_between_rays = (float)FOV / proj_plan_width;
	
	// variante
	
	// double angle = 60;
	
	double playr_x = 224;
	double playr_y = 224;
	
	// check horizontal intersection
	
	/*
		if the ray is facing up YA = -64 else Ya = 64 
		Note** :: if (the angle between 0 && 180.0 the ray is facing up) else is facing down
		if the ary is in the right xa = 64 / tan(angle * (M_PI / 180.0)) else xa will be negative
		Note** :: if (the angle between 0 && 90 or the angle between 277 && 360 the ray is in the right) else is in the left
	*/


	double Ya = -64;
	double Xa = 64 / tan(angle * (M_PI / 180.0));
	
	double first_horz_inter_y = ((int)floor((int)playr_y >> wall_height_shift) << wall_height_shift) - 1;
	double first_horz_inter_x = playr_x + (playr_y - first_horz_inter_y) / tan(angle * (M_PI / 180.0));
	// double chart = (playr_y - first_horz_inter_y) / tan(angle * (M_PI / 180.0));
	// double first_horz_inter_x = playr_x + chart;
	
	// if (angle >= 90)
	// {
	// 	Xa *= -1;
	// 	first_horz_inter_x = playr_x - chart;
	// }
		
	int i = (int)first_horz_inter_y  >> wall_height_shift;
	int j = (int)first_horz_inter_x  >> wall_height_shift;
		
	while (i < 5 && i >= 0 && j < 5 && j >= 0 && map[i][j] != 1)
	{
		first_horz_inter_y += Ya;
		first_horz_inter_x += Xa;
		i = (int)first_horz_inter_y >> wall_height_shift;
		j = (int)first_horz_inter_x >> wall_height_shift;
	}
		
	// check vertical intersection
	
	double vert_Xa = wall_height;
	double vert_Ya = vert_Xa * tan(angle * (M_PI / 180.0));
	
	// if (angle >= 90)
	// 	vert_Xa *= -1;
	
	double first_vert_inter_x = ((int)floor((int)playr_x >> wall_height_shift) << wall_height_shift) + vert_Xa;
	double first_vert_inter_y = playr_y - ((first_vert_inter_x - playr_x) * tan(angle * (M_PI / 180.0)));
	
	i = (int)first_vert_inter_y  >> wall_height_shift;
	j = (int)first_vert_inter_x  >> wall_height_shift;
		
	while (i < 5 && i >= 0 && j < 5 && j >= 0 && map[i][j] != 1)
	{
		first_vert_inter_y -= vert_Ya;
		first_vert_inter_x += vert_Xa;
		i = (int)first_vert_inter_y >> wall_height_shift;
		j = (int)first_vert_inter_x >> wall_height_shift;
	}
	
	double horz_dist = (double)fabs(playr_y - first_horz_inter_y) / sin(angle * (M_PI / 180.0));
	double vert_dist = (double)fabs(playr_y - first_vert_inter_y) / sin(angle * (M_PI / 180.0));
	
	double ray = horz_dist;
	if (ray > vert_dist)
		ray = vert_dist;
		
	// double beta_angle = angle - 90;
	// if (angle >= 90)
	// 	beta_angle *= -1;
	// double	beta = fmod(angle - 90, 360);
	ray = (double)ray * cos((angle - 90) * (M_PI / 180.0));
	
	double actual_height = ceil((64 * 277) / ray);
	
	draw_line(mlx_ptr, mlx_win, start, (100 - (actual_height / 2)), (100 - (actual_height / 2)) + actual_height);

	(void)data;
	return (0);
}