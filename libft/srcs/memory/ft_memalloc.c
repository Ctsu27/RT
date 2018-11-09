/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:30:41 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:30:43 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	int		*dest;

	if ((dest = (int *)malloc(sizeof(*dest) * size)) == NULL)
		return (NULL);
	while (size > 0)
	{
		dest[size - 1] = 0;
		size--;
	}
	return (dest);
}
