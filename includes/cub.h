/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:12:48 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/20 00:30:19 by onouakch         ###   ########.fr       */
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

typedef struct s_mapelements
{
    char *north_text;
    char *south_test;
    char *west_text;
    char *east_text;
    t_rgb *rgb;
} t_mapelements;


int check_element(int map);


# endif
