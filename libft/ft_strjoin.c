/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:42:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/22 13:54:50 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (free((char *)s2), NULL);
	else if (!s2)
		return (free((char *)s1), NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (free((char *)s1), free((char *)s2), NULL);
	i = -1;
	j = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	while (++j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
	}
	return (str);
}
