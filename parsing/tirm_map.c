/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tirm_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 09:28:29 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/27 05:28:57 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	start_spaces(char **map)
{
	int	i;
	int	j;
	int	count;
	int	min;

	i = 0;
	min = ft_strlen_width(map);
	while (map[i])
	{
		j = 0;
		count = 0;
		while (map[i][j] && map[i][j] == ' ')
		{
			count++;
			j++;
		}
		if (count < min)
			min = count;
		i++;
	}
	return (min);
}

static void	end_spaces(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map_data.map[++i])
	{
		j = ft_strlen(data->map_data.map[i]) - 1;
		while (j >= 0 && data->map_data.map[i][j] == ' ')
		{
			data->map_data.map[i][j] = '\0';
			j--;
		}
	}
}

void	trim_map(t_data *data)
{
	int	start;
	int	i;
	int	j;

	end_spaces(data);
	start = start_spaces(data->map_data.map);
	i = -1;
	while (data->map_data.map[++i])
	{
		j = 0;
		while (data->map_data.map[i][j] && data->map_data.map[i][j + start])
		{
			data->map_data.map[i][j] = data->map_data.map[i][j + start];
			j++;
		}
		data->map_data.map[i][j] = '\0';
	}
}

int	join_nulls(t_data *data)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (i < (int)ft_strlen_height(data->map_data.map))
	{
		str = ft_calloc((ft_strlen_width(data->map_data.map) + 1), \
			sizeof(char));
		if (!str)
			return (1);
		j = 0;
		while (j < (int)ft_strlen(data->map_data.map[i]))
		{
			str[j] = data->map_data.map[i][j];
			j++;
		}
		free(data->map_data.map[i]);
		data->map_data.map[i] = str;
		i++;
	}
	return (0);
}

int	check_extension(int ac, char *av[])
{
	int	index;

	index = 0;
	if (ac != 2)
		return (fatal("Wrong number of arguments"), 1);
	if (ft_strlen(av[1]) < 5)
		return (fatal("Wrong file extension"), 1);
	else
	{
		index = ft_strlen(av[1]) - 1;
		if (av[1][index] != 'b' || av[1][index - 1] != 'u' || av[1][index
			- 2] != 'c' || av[1][index - 3] != '.')
			return (fatal("Wrong file extension"), 1);
	}
	return (0);
}
