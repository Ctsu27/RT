/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbuf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:20:41 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/25 19:26:04 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lbuf.h"

int		lbuf_init(t_lbuf *buf, char const *path,
		int const mods, int const rights)
{
	if (!path)
		buf->fd = 1;
	else if (rights != 0)
	{
		if ((buf->fd = open(path, mods, rights)) < 0)
			return (-1);
	}
	else if ((buf->fd = open(path, mods)) < 0)
		return (-1);
	buf->size = 0;
	return (0);
}
