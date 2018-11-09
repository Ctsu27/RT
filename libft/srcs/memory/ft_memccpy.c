/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:30:48 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:30:49 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*srcs;
	size_t			i;

	i = 0;
	c = (unsigned char)c;
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	while (i < n)
	{
		if (srcs[i] != c)
		{
			dest[i] = srcs[i];
			i++;
		}
		else
		{
			dest[i] = c;
			return (dest + i + 1);
		}
	}
	return (NULL);
}
