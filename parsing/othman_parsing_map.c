/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othman_parsing_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:06:15 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/20 04:27:23 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int parse_rgb(char *rgb_str, t_rgb *rgb)
{
    (void)rgb_str;
    (void)rgb;
    return (1);
}

int parse_element(char *identifier, char *path_rgb, t_data *data, int *all_in)
{
    int path_fd;
    if (ft_strlen(identifier) == 1)
    {
        if (!ft_strcmp(identifier, "F") && data->map_data.map_elements.frgb.r == -1)
        {
            if (!parse_rgb(path_rgb, &data->map_data.map_elements.frgb))
                return (fatal("Invalid colors"), 0);
        }
        else if(!ft_strcmp(identifier, "C") && data->map_data.map_elements.crgb.r == -1)
        {
            if (!parse_rgb(path_rgb, &data->map_data.map_elements.crgb))
                return (fatal("Invalid colors"), 0);
        }
        else
            return (fatal("Invalid | Duplicate identifer"), 0);
    }
    else
    {
        path_fd = open(path_rgb, O_RDONLY);
        if (path_fd == -1)
            return (fatal("Invalid path for textures"), 0);
        if (!ft_strcmp(identifier, "NO") && !data->map_data.map_elements.north_text)
            data->map_data.map_elements.north_text = path_rgb;
        else if (!ft_strcmp(identifier, "SO") && !data->map_data.map_elements.south_text)
            data->map_data.map_elements.south_text = path_rgb;
        else if (!ft_strcmp(identifier, "WE") && !data->map_data.map_elements.west_text)
            data->map_data.map_elements.west_text = path_rgb;
        else if (!ft_strcmp(identifier, "EA") && !data->map_data.map_elements.east_text)
            data->map_data.map_elements.east_text = path_rgb;
        else
            return (fatal("Invalid | Duplicate identifier"), 0);
    }
    *all_in = *all_in + 1;
    return (1);
}

char *remove_newline(char *line)
{
    char *tmp;

    tmp = line;
    line = ft_substr(line, 0, ft_strlen(line) - 1);
    return (free(tmp), line);
}

int check_element(int map, t_data *data)
{
    int     all_in;
    char    *line;
    char    **av;
    char    *tmp;

    all_in = 0;
    while (all_in < 6)
    {
        tmp = get_next_line(map);
        tmp = remove_newline(tmp);
        line = ft_strtrim(tmp, " ");
        free(tmp);
        if (ft_count_words(line, ' ') != 2)
        {
            if (!ft_strcmp(line, ""))
            {
                free(line);
                continue;
            }
            else
                return (free(line), fatal("too much data"), 0);
        }
        av = ft_split(line, ' ');
        if (ft_strlen(av[0]) > 2 || !parse_element(av[0], av[1], data, &all_in))
            return (fatal("Invalid identifier"), 0);
    }
    return (1);
}