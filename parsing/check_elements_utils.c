/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:32:16 by onouakch          #+#    #+#             */
/*   Updated: 2023/09/27 04:32:01 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	is_numeric(char *str)
{
	int		check_space;
	int		i;

	i = -1;
	check_space = 0;
	while (str[++i] && str[i] == ' ')
		;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == ' ')
				check_space = 1;
			else
				return (0);
		}
		else if (check_space)
			return (0);
		i++;
	}
	return (1);
}

int	count_commas(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == ',')
			count++;
	return (count);
}

int	parse_rgb(char *rgb_str, t_rgb *rgb)
{
	char	**args;
	int		i;

	if (count_commas(rgb_str) != 2)
		return (0);
	args = ft_split(rgb_str, ',');
	if (!args)
		return (0);
	if (!args[0] || !args[1] || !args[2])
		return (free_map(args), 0);
	i = 3;
	while (--i >= 0)
		if (!is_numeric(args[i]))
			return (free_map(args), 0);
	rgb->r = ft_atoi(args[0]);
	rgb->g = ft_atoi(args[1]);
	rgb->b = ft_atoi(args[2]);
	if (rgb->r > 255 || rgb->g > 255 || rgb->b > 255)
		return (free_map(args), 0);
	return (free_map(args), 1);
}

char	*remove_newline(char *line)
{
	char	*tmp;

	tmp = line;
	line = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!line)
		return (NULL);
	return (free(tmp), line);
}

int	read_line(int map, char **line)
{
	free(*line);
	*line = get_next_line(map);
	if (!*line)
		return (0);
	*line = remove_newline(*line);
	if (!*line)
		return (0);
	return (1);
}
