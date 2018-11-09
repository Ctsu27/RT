/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:32:21 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:32:22 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*srcs;
	size_t			i;

	i = 0;
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dst);
}
