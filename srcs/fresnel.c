/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:02:33 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/27 17:32:17 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt_ts.h"

static void	swap_double(double *a, double *b)
{
	static double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double		fresnel(t_ray const ray, t_vec3 const inter, t_vec3 const normal,
		double const ior)
{
	static t_vec3	view;
	static double	cos[2];
	static double	eta[2];
	static double	r[2];
	static double	sin_t;

	view = sub_vec3(inter, ray.pos);
	cos[0] = dot_vec3(normal, view);
	eta[0] = ior;
	eta[1] = 1.0;
	if (cos[0] < 0)
		swap_double(eta, eta + 1);
	sin_t = (eta[0] / eta[1]) * fmax(0.0, 1.0 - cos[0] * cos[0]);
	if (sin_t >= 1.0)
		return (1.0);
	cos[1] = fmax(0.0, 1.0 - sin_t * sin_t);
	cos[0] = (cos[0] < 0.0) ? -cos[0] : cos[0];
	r[0] = (eta[1] * cos[0] - eta[0] * cos[1])
		/ (eta[1] * cos[0] + eta[0] * cos[1]);
	r[1] = (eta[0] * cos[0] - eta[1] * cos[1])
		/ (eta[0] * cos[0] + eta[1] * cos[1]);
	return ((r[0] * r[0] + r[1] * r[1]) / 2);
}
