/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:15:33 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/25 19:25:11 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SBUF_H
# define SBUF_H

# define SBUFF_SIZE 4096

typedef struct	s_sbuf
{
	int				fd;
	unsigned short	size;
	char			s[SBUFF_SIZE];
}				t_sbuf;

int		sbuf_init(t_sbuf *buf, char const *path, int const mods,
		int const rights);
void	sbuf_in(t_sbuf *buf, char const *src);
void	sbuf_out(t_sbuf *buf);
#endif
