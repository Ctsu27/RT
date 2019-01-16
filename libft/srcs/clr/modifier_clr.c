/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_clr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 23:01:59 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/16 23:02:11 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "clr.h"

static t_clr	gray(t_clr const pxl)
{
	double	average;

	average = (pxl.r + pxl.g + pxl.b) / 765.0 * 255.0;
	return (new_clr(test, test, test, pxl.a));
}

static t_clr	deuteranomaly(t_clr const pxl)
{
	return (new_clr((pxl.r * 0.8) + (pxl.g * 0.2),
				(pxl.r * 0.258) + (pxl.g * 0.742),
				(pxl.g * 0.142) + (pxl.b * 0.858),
				pxl.a));
}

static t_clr	sepia(t_clr const pxl)
{
	t_clr	n;

	n.r = fmin((pxl.r * 0.393) + (pxl.g * 0.769) + (pxl.b * 0.189), 255.0);
	n.g = fmin(((pxl.r * 0.349) + (pxl.g * 0.686) + (pxl.b * 0.168)), 255.0);
	n.b = fmin(((pxl.r * 0.272) + (pxl.g * 0.534) + (pxl.b * 0.131)), 255.0);
	return (n);
}

t_clr			modifier_clr(t_clr const pxl, int const filter)
{
	static t_clr	(*g_modifier[3])(t_clr const) = {
		[FILTER_SEPIA] = &sepia,
		[FILTER_GRAY] = &gray,
		[FILTER_DEUTERANOMALY] = &deuteranomaly
	};

	if (filter == FILTER_NONE)
		return (pxl);
	return (g_modifier[filter](pxl));
}
