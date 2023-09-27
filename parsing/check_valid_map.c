/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:17:59 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/27 11:19:31 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_map_is_valid(int map_fd, t_data *data)
{
	if (!check_element(map_fd, data))
		return (1);
	if (check_map_pars(map_fd, data))
		return (1);
	return (0);
}
