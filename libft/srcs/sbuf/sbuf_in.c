/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuf_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:16:13 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/25 19:31:28 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strft.h"
#include "sbuf.h"

/*
**	need to change concatenation
*/

void	sbuf_in(t_sbuf *buf, char const *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		if (buf->size >= SBUFF_SIZE)
			sbuf_out(buf);
		buf->s[buf->size] = src[i];
		buf->size++;
		i++;
	}
}
