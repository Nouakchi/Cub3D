/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 07:55:56 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/27 05:27:27 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (free(s2), NULL);
	else if (!s2)
		return (free(s1), NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (free(s1), free(s2), NULL);
	i = -1;
	j = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	while (++j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
	}
	return (free(s1), free(s2), str);
}

char	*get_init_map(int fd)
{
	char	*init_map;
	char	*line;

	init_map = ft_strdup("");
	if (!init_map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		init_map = ft_strjoin_free(init_map, line);
		if (!init_map)
			return (NULL);
		line = get_next_line(fd);
	}
	return (init_map);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
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

int	check_map_is_valid(int map_fd, t_data *data)
{
	if (!check_element(map_fd, data))
		return (1);
	if (check_map_pars(map_fd, data))
		return (1);
	return (0);
}
