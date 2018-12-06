/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gi_ray_distorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:02 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/06 12:23:18 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_clr			gi_ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	static t_vec3	view;
	static double	tmp[3];
	static double	ior = 1.5;

	view = sub_vec3(hit.pos, ray.pos);
	tmp[0] = dot_vec3(hit.normal, view);
	if (tmp[0] < 0)
	{
		tmp[0] = -tmp[0];
		tmp[1] = 1.0 / ior;
	}
	else
		tmp[1] = ior;
	if ((tmp[2] = 1.0 - tmp[1] * tmp[1] * (1.0 - tmp[0] * tmp[0])) < 0.0)
	{
		tmp[1] = 1.0;
		tmp[2] = 1.0 - tmp[0] * tmp[0];
	}
	ray.pos = hit.pos;
	ray.dir = norm_vec3(add_vec3(mul_vec3(hit.normal, tmp[1]),
				mul_vec3(hit.normal, tmp[1] * tmp[0] - sqrt(tmp[2]))));
	return (mul_clr(raytrace_diffuse(core, ray, rebound),
				1.0 - hit.obj->absorption));
}

t_clr			gi_ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	static t_vec3	view;

	view = sub_vec3(ray.pos, hit.pos);
	ray.pos = hit.pos;
	ray.dir = norm_vec3(sub_vec3(mul_vec3(hit.normal,
					2.0 * dot_vec3(hit.normal, view)), view));
	return (mul_clr(raytrace_diffuse(core, ray, rebound),
				1.0 - hit.obj->absorption));
}

t_clr			gi_ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound)
{
	double	k;

	k = fresnel(ray, inter.pos, inter.normal, 1.5);
	return (add_clr(mul_clr(gi_ray_trace_reflection(core, ray, inter, rebound),
					k),
				mul_clr(gi_ray_trace_refraction(core, ray, inter, rebound),
					1.0 - k)));
}
