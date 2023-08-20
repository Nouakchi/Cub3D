/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_init_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 07:55:56 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/20 06:38:49 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_main.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		ft_error("Error\nMalloc Error", s2, NULL);
	else if (!s2)
		ft_error("Error\nMalloc Error", s1, NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
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
	line = get_next_line(fd);
	while (line)
	{
		init_map = ft_strjoin_free(init_map, line);
		line = get_next_line(fd);
	}
	return (init_map);
}

void	ft_error_open(int fd)
{
	if (fd < 0)
		ft_error("Error\nOpen Error", NULL, NULL);
}

void	ft_error(char *msg, char *free_str1, char *free_str2)
{
	free(free_str1);
	free(free_str2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}
