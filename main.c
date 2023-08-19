/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/20 00:00:10 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"

int main(int ac, char *av[])
{
    int map_fd;

    if (ac != 2)
        return (write(1, "Error\n", 6), 0);
    map_fd = open(av[1], O_RDONLY);
    if (map_fd == -1)
        return (write(1, "Error\n", 6), 0);
    if (!check_element(map_fd))
        return (write(1, "Error\n", 6), 0);
    printf("%s", get_next_line(map_fd));
    return (0);
}