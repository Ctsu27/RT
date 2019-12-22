/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pxl_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:47:46 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/31 14:52:53 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "clr.h"

void		mlx_put_pxl_img(unsigned char *img, t_clr const c,
		int const x, int const y)
{
	static int const	sizeline = WIN_W * 4;
	unsigned long		i;

	i = x * 4 + y * sizeline;
	img[i] = (unsigned char)(c.b + 0.5);
	img[i + 1] = (unsigned char)(c.g + 0.5);
	img[i + 2] = (unsigned char)(c.r + 0.5);
	img[i + 3] = (unsigned char)(c.a + 0.5);
}
