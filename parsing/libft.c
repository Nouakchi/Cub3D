/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 07:55:44 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 08:06:09 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_01snew.h"

int	ft_strlen(char *s)
{
	size_t	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x])
		x++;
	return (x);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		ls1;
	int		ls2;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = (char *)ft_calloc((ls1 + ls2 + 1) * sizeof(char));
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
	return (free(s1), str);
}

char	*ft_strdup(char *s1)
{
	char	*s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	s = (char *)ft_calloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	unsigned char	*a;
	void	*p;

	i = -1;
	if (count)
	{
		if (size >= i / count)
			return (NULL);
	}
	if (size)
	{
		if (count >= i / size)
			return (NULL);
	}
	p = malloc(count * size);
	if (!p)
		return (NULL);
	a = (unsigned char *)p;
	while (++i < count * size)
		a[i] = 0;
	return (p);
}
