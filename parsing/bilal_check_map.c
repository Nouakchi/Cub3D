/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 08:51:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/21 13:45:27 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	trim_end(char *m)
{
	int	i;

	i = ft_strlen(m) - 1;
	while (i >= 0 && m[i] == ' ')
	{
		m[i] = '\0';
		i--;
	}
}

int     check_map_pars(int map_fd, t_data *data)
{
	char   *init_map;

	init_map = get_init_map(map_fd);
	init_map = ft_strtrim(init_map, "\n");
	trim_end(init_map);
	if (check_init_map(init_map))
		return (free(init_map), 1);
	data->map_data.map = ft_split(init_map, '\n');
	join_nulls(data);
	if (!data->map_data.map)
		return (free(init_map), 1);
	free(init_map);
	if (check_map(data->map_data.map))
		return (1);
	return (0);
}

int	check_chars(char *map)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (map[++i])
	{
		if (map[i] == 'S' || map[i] == 'N' || map[i] == 'E' || map[i] == 'W')
			c++;
		if (c > 1)
			return (1);
		if (check_chars_utils(map[i]))
			return (1);
	}
	if (c == 0)
		return (1);
	return (0);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (i == 0 || i == ft_strlen_height(map) - 1 || j == 0
				|| j == (int)ft_strlen(map[i]) - 1)
			{
				if (map[i][j] != ' ' && map[i][j] != '1')
					return (1);
			}
			if (map[i][j] != ' ' && map[i][j] != '1')
			{
				if (check_walls_utils(map, i, j))
					return (1);
			}
		}
	}
	return (0);
}

int	check_newline(char *map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
			return (1);
	}
	return (0);
}

int	check_init_map(char *map)
{
	if (check_newline(map))
		return (1);
	if (check_chars(map))
		return (1);
	return (0);
}

int	check_map(char **map)
{
	if (ft_strlen_height(map) < 3 || ft_strlen_width(map) < 3)
		return (1);
	if (check_walls(map))
		return (1);
	return (0);
}










// join_nulls(&data);

void join_nulls(t_data *data)
{
	char	*str;
	int i;
	int j;

	i = 0;
	while (i < (int)ft_strlen(data->map_data.map[i]))
	{
		str = ft_calloc((ft_strlen_width(data->map_data.map) + 1), sizeof(char));
		if (!str)
			return ;
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
}
