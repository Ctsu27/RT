/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distorted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:44:19 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/18 21:53:17 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_clr			ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	double	dot;
	double	eta;
	double	k;

	dot = dot_vec3(hit.normal, ray.dir);
	if (dot < 0.)
	{
		dot = -dot;
		eta = 1.0 / hit.obj->ior;
	}
	else
		eta = hit.obj->ior;
	k = 1.0 - eta * eta * (1.0 - dot * dot);
	if (k < 0.)
	{
		eta = 1.0;
		k = 1.0 - dot * dot;
	}
	ray.pos = hit.pos;
	ray.dir = norm_vec3(add_vec3(mul_vec3(ray.dir, eta),
				mul_vec3(hit.normal, eta * dot - sqrt(k))));
	return (mul_clr(raytrace(core, ray, rebound), 1.0 - hit.obj->clr.a));
}

t_clr			ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	t_vec3	view;

	view = sub_vec3(ray.pos, hit.pos);
	ray.pos = hit.pos;
	ray.dir = norm_vec3(sub_vec3(mul_vec3(hit.normal,
					2.0 * dot_vec3(hit.normal, view)), view));
	return (mul_clr(raytrace(core, ray, rebound), 1.0 - hit.obj->clr.a));
}

t_clr			ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound)
{
	double	k;

	k = fresnel(ray, hit.pos, hit.normal, hit.obj->ior);
	return (add_clr(mul_clr(ray_trace_reflection(core, ray, hit, rebound), k),
				mul_clr(ray_trace_refraction(core, ray, hit, rebound),
					1.0 - k)));
}
