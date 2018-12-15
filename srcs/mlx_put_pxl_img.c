/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pxl_img.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:47:46 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:48:45 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "clr.h"

void		mlx_put_pxl_img(char *img, t_clr const c,
		int const x, int const y)
{
	static int const	sizeline = WIN_W * 4;
	unsigned long		i;

	i = x * 4 + y * sizeline;
	img[i] = (char)(c.r + 0.5);
	img[i + 1] = (char)(c.g + 0.5);
	img[i + 2] = (char)(c.b + 0.5);
	img[i + 3] = (char)(c.a + 0.5);
}
