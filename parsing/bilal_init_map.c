/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_init_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 07:55:56 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 11:15:12 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bilal_map_01snew.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		ft_error("Error\nMalloc Error", s1, NULL);
	else if (!s2)
		ft_error("Error\nMalloc Error", s2, s2);
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

char	**get_init_map(int fd)
{
	char	*my_backup;
	char	*buff;
	int		nb;
	char	**map;

	my_backup = ft_strdup("");
	nb = -1;
	while (1)
	{
		buff = (char *)ft_calloc(2, sizeof(char));
		if (!buff)
			ft_error("Error\nMalloc Error", my_backup, NULL);
		nb = read(fd, buff, 1);
		if (nb == -1)
			ft_error("Error\nRead Error", my_backup, buff);
		if (nb == 0 && my_backup[0])
			break ;
		if (nb == 0)
			ft_error("Error\nThe map is empty", my_backup, NULL);
		my_backup = ft_strjoin_free(my_backup, buff);
	}
	map = ft_split(my_backup, '\n');
	if (!map)
		ft_error("Error\nMalloc Error", my_backup, buff);
	return (free(buff), free(my_backup), map);
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
