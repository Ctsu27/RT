/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbuf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:19:46 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/26 09:50:20 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LBUF_H
# define LBUF_H

# include "slst.h"

# define LBUFF_SIZE 4096

typedef struct	s_lbuf
{
	t_slst			*head;
	t_slst			*ptr;
	int				fd;
	unsigned short	size;
}				t_lbuf;

int		lbuf_init(t_lbuf *buf, char const *path, int const mods,
		int const rights);
void	lbuf_in(t_lbuf *buf, char const *src);
void	lbuf_out(t_lbuf *buf);
#endif
