/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gi_ray_distorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:02 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/04 23:20:24 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_clr			gi_ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	t_vec3	view;
	double	tmp[3];

	view = norm_vec3(sub_vec3(hit.pos, ray.pos));
	tmp[0] = dot_vec3(hit.normal, view);
	if (tmp[0] < 0)
	{
		tmp[0] = -tmp[0];
		tmp[1] = 1.0 / hit.obj->ior;
	}
	else
		tmp[1] = hit.obj->ior;
	if ((tmp[2] = 1.0 - tmp[1] * tmp[1] * (1.0 - tmp[0] * tmp[0])) < 0.0)
	{
		tmp[1] = 1.0;
		tmp[2] = 1.0 - tmp[0] * tmp[0];
	}
	ray.pos = hit.pos;
	ray.dir = norm_vec3(add_vec3(mul_vec3(view, tmp[1]),
				mul_vec3(hit.normal, tmp[1] * tmp[0] - sqrt(tmp[2]))));
	return (mul_clr(raytrace_diffuse(core, ray, rebound),
				1.0 - hit.obj->clr.a));
}

t_clr			gi_ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	t_vec3	view;

	view = sub_vec3(ray.pos, hit.pos);
	ray.pos = hit.pos;
	ray.dir = norm_vec3(sub_vec3(mul_vec3(hit.normal,
					2.0 * dot_vec3(hit.normal, view)), view));
	return (mul_clr(raytrace_diffuse(core, ray, rebound),
				1.0 - hit.obj->clr.a));
}

t_clr			gi_ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	double	k;

	k = fresnel(ray, hit.pos, hit.normal, hit.obj->ior);
	return (add_clr(mul_clr(gi_ray_trace_reflection(core, ray, hit, rebound),
					k),
				mul_clr(gi_ray_trace_refraction(core, ray, hit, rebound),
					1.0 - k)));
}
