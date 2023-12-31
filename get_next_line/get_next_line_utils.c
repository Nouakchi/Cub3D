/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:11:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/22 13:48:27 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gl_strlen(char *s)
{
	size_t	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x])
		x++;
	return (x);
}

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

char	*gl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	ls1;
	size_t	ls2;

	ls1 = gl_strlen(s1);
	ls2 = gl_strlen(s2);
	str = (char *)malloc((ls1 + ls2 + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	i = -1;
	j = -1;
	while (++i < ls1)
		str[i] = s1[i];
	while (++j < ls2)
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*gl_strdup(char *s1)
{
	char	*s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	s = (char *)malloc((gl_strlen(s1) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
