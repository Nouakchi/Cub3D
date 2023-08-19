/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:05:03 by onouakch          #+#    #+#             */
/*   Updated: 2023/08/19 23:35:42 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"

int main(int ac, char *av[])
{
    int map;

    if (ac != 2)
        return (write(1, "Error\n", 6), 0);
    map = open(av[1], O_RDONLY);
    if (map == -1)
        return (write(1, "Error\n", 6), 0);
    return (0);
}