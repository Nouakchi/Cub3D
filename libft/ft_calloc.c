/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:55:41 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/22 14:08:54 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
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
	p = malloc(-1);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);


}
