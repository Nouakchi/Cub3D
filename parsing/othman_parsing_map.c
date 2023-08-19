/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othman_parsing_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:06:15 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/20 00:54:42 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int check_element(int map)
{
    int     all_in;
    char    *line;
    // char    **args;

    all_in = 0;
    while (all_in < 6)
    {
        line = get_next_line(map);
        printf("%s", line);
        if (ft_count_words(line, ' ') != 2)
            return (free(line), 0);
        // args = ft_split(line, ' ');
    }
    return (1);
}