/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 07:55:56 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 08:17:48 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_01snew.h"

int	is_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_error(char *msg, char *free_str1, char *free_str2)
{
	free(free_str1);
	free(free_str2);
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
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
			return (free(buff), my_backup);
		if (nb == 0)
			ft_error("Error\nThe map is empty", my_backup, NULL);
		my_backup = ft_strjoin(my_backup, buff);
		free(buff);
	}
	
	return (my_backup);
}

// ------------------------------------------

void	ft_error_open(int fd)
{
	if (fd < 0)
		ft_error("Error\nOpen Error", NULL, NULL);
}
