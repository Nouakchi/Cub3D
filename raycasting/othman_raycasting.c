/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othman_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:37:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/22 15:51:34 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	render(t_data *data)
{
	void *mlx_ptr;
	void *mlx_win;
	
	char map[5][5] = {
		{1,1,1,1,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,9,0,0,1},
		{1,1,1,1,1},
	};
	
	//
	// int player_height = 32;
	double wall_height = 64.0;
	int wall_height_shift = log2(wall_height);
	
	// int FOV = 60;
	int proj_plan_width = 320;
	int proj_plan_height = 200;
	// int dist_plyr_to_projplan = (proj_plan_width / 2) / tan((FOV / 2.0) * (M_PI / 180));
		
	// int dimension_proj_plan = proj_plan_width * proj_plan_height;
		
	// int center_proj_plan_x = proj_plan_width / 2;
	// int center_proj_plan_y = proj_plan_height / 2;

	// float angle_between_rays = (float)FOV / proj_plan_width;
	
	// variante
	
	double angle = 60;
	
	int playr_x = 96;
	int playr_y = 224;
	
	// check horizontal intersection
	
	/*
		if the ray is facing up YA = -64 else Ya = 64 
		Note** :: if (the angle between 0 && 180 the ray is facing up) else is facing down
		if the ary is in the right xa = 64 / tan(angle * (M_PI / 180)) else xa will be negative
		Note** :: if (the angle between 0 && 90 or the angle between 277 && 360 the ray is in the right) else is in the left
	*/
	int Ya = -64;
	int Xa = 64 / tan(angle * (M_PI / 180));
	
	int first_horz_inter_y = ((int)floor(playr_y >> wall_height_shift) << wall_height_shift) - 1;
	int first_horz_inter_x = playr_x + (playr_y - first_horz_inter_y) / tan(angle * (M_PI / 180));
		
	int i = first_horz_inter_y  >> wall_height_shift;
	int j = first_horz_inter_x  >> wall_height_shift;
	
	while (map[i][j] != 1)
	{
		first_horz_inter_y += Ya;
		first_horz_inter_x += Xa;
		i = first_horz_inter_y >> wall_height_shift;
		j = first_horz_inter_x >> wall_height_shift;
	}
	
	if (map[i][j] == 1)
		printf("horizontal Wall intersection found at [%d,%d] => %d\n", i, j, map[i][j]);
		
	// check vertical intersection
	
	int vert_Xa = wall_height;
	int vert_Ya = (vert_Xa * tan(angle * (M_PI / 180)));
	
	int first_vert_inter_x = ((int)floor(playr_x >> wall_height_shift) << wall_height_shift) + 64;
	int first_vert_inter_y = playr_y - ((first_vert_inter_x - playr_x) * tan(angle * (M_PI / 180)));
	
	printf("[%d,%d]\n", first_vert_inter_x, first_vert_inter_y);

	i = first_vert_inter_y  >> wall_height_shift;
	j = first_vert_inter_x  >> wall_height_shift;

	printf("[%d,%d] => %d\n", i, j, map[i][j]);
	
	while (map[i][j] != 1)
	{
		first_vert_inter_y -= vert_Ya;
		first_vert_inter_x += vert_Xa;
		i = first_vert_inter_y >> wall_height_shift;
		j = first_vert_inter_x >> wall_height_shift;
	}
	
	if (map[i][j] == 1)
		printf("Vertical Wall intersection found at [%d,%d] => %d\n", i, j, map[i][j]);
	


	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, proj_plan_width, proj_plan_height, "cub3D");
	
	


	mlx_pixel_put(mlx_ptr, mlx_win, 0,0,0x00ff0000);
	mlx_loop(mlx_ptr);
	(void)data;
	return (0);
}