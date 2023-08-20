/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/20 04:26:45 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"

void fatal(char *mssg)
{
    printf("Error\n%s\n", mssg);
    exit(0);
}

void data_init(t_data *data)
{
    data->map_data.map_elements.east_text = NULL;
    data->map_data.map_elements.west_text = NULL;
    data->map_data.map_elements.north_text = NULL;
    data->map_data.map_elements.south_text = NULL;
    data->map_data.map = NULL;
    data->map_data.map_elements.frgb.r = -1;
    data->map_data.map_elements.crgb.r = -1;
}

int main(int ac, char *av[])
{
    int     map_fd;
    t_data  data;

    if (ac != 2)
        return (fatal("Few arguments !!"), 0);
    map_fd = open(av[1], O_RDONLY);
    if (map_fd == -1)
        return (fatal("Invalid file !!"), 0);
    data_init(&data);
    check_element(map_fd, &data);
    printf("%s\n", data.map_data.map_elements.north_text);
    printf("%s\n", data.map_data.map_elements.west_text);
    printf("%s\n", data.map_data.map_elements.east_text);
    printf("%s\n", data.map_data.map_elements.south_text);
    printf("%d,%d,%d\n", data.map_data.map_elements.frgb.r,data.map_data.map_elements.frgb.g,data.map_data.map_elements.frgb.b);
    printf("%d,%d,%d\n", data.map_data.map_elements.crgb.r,data.map_data.map_elements.crgb.g,data.map_data.map_elements.crgb.b);
    
    return (0);
}