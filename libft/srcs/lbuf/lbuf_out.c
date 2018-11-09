/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbuf_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:20:42 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/26 09:50:59 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lbuf.h"

void	lbuf_out(t_lbuf *buf)
{
	if (buf->fd >= 0)
	{
		write(buf->fd, (char *)(buf->ptr)->data, buf->size);
		buf->size = 0;
	}
}
