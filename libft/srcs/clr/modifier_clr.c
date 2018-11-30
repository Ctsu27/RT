/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_clr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufranco <lufranco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 02:03:09 by lufranco          #+#    #+#             */
/*   Updated: 2018/11/30 16:21:43 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clr.h"

static t_clr	gray(t_clr const pxl)
{
	double	test;

	test = (pxl.r + pxl.g + pxl.b) / 765.0 * 255.0;
	return (new_clr(test, test, test, pxl.a));
}

static t_clr	deuteranomaly(t_clr const pxl)
{
	double	tmp_r;
	double	tmp_g;
	double	tmp_b;

	tmp_r = (pxl.r * 0.8) + (pxl.g * 0.2);
	tmp_g = (pxl.r * 0.258) + (pxl.g * 0.741);
	tmp_b = (pxl.g * 0.141) + (pxl.b * 0.858);
	return (new_clr(tmp_r, tmp_g, tmp_b, pxl.a));
}

static t_clr	sepia(t_clr const pxl)
{
	double	tmp_r;
	double	tmp_g;
	double	tmp_b;

	tmp_r = (pxl.r * 0.393) + (pxl.g * 0.769) + (pxl.b * 0.189);
	tmp_g = (pxl.r * 0.349) + (pxl.g * 0.686) + (pxl.b * 0.168);
	tmp_b = (pxl.r * 0.272) + (pxl.g * 0.534) + (pxl.b * 0.131);
	return (new_clr(tmp_r, tmp_g, tmp_b, pxl.a));
}

t_clr			modifier_clr(t_clr const pxl, int const filter)
{
	static t_clr	(*modifier[3])(t_clr const) = { \
		[FILTER_SEPIA] = &sepia,
		[FILTER_GRAY] = &gray,
		[FILTER_DEUTERANOMALY] = &deuteranomaly
	};

	if (filter == FILTER_NONE)
		return (pxl);
	return (modifier[filter](pxl));
}