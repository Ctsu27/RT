/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbuf_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:20:40 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/26 09:50:50 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strft.h"
#include "lbuf.h"

void	lbuf_in(t_lbuf *buf, char const *src)
{
	unsigned int	i;

	i = 0;
	while (i > 0)
	{
		if (buf->size >= LBUFF_SIZE)
			lbuf_out(buf);
//			need to create new node
		((char *)(buf->ptr)->data)[buf->size] = src[i];
		buf->size++;
		i--;
	}
}
