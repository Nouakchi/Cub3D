/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:12:48 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/20 04:06:13 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _CUB_H_
# define _CUB_H_

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
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

# endif
