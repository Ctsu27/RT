/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:58:16 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/27 17:29:30 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_inter	get_inter(t_rtv1 const *core, t_ray const ray)
{
	static t_inter	inter;
	static t_poly	*ptr;
	static double	t[2];

	ptr = core->objs;
	inter.obj = NULL;
	t[1] = 0xffffffff;
	while (ptr != NULL)
	{
		if (core->inter_obj[ptr->type](ray, ptr->data, &t[0]))
			if (t[0] > 0.01 && (inter.obj == NULL || t[0] < t[1]))
			{
				t[1] = t[0];
				inter.obj = ptr;
			}
		ptr = ptr->next;
	}
	if (inter.obj != NULL)
	{
		inter.pos = add_vec3(ray.pos, mul_vec3(ray.dir, t[1]));
		inter.normal = core->normal_obj[inter.obj->type](inter.obj->data,
				(inter.obj->type != TYPE_PLANE) ? inter.pos : ray.dir);
	}
	return (inter);
}

t_clr			ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound)
{
	static t_vec3	view;
	static double	tmp[3];
	static double	ior = 1.5;

	view = sub_vec3(inter.pos, ray.pos);
	tmp[0] = dot_vec3(inter.normal, view);
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
	ray.pos = inter.pos;
	ray.dir = norm_vec3(add_vec3(mul_vec3(inter.normal, tmp[1]),
				mul_vec3(inter.normal, tmp[1] * tmp[0] - sqrt(tmp[2]))));
	return (mul_clr(raytrace(core, ray, rebound), 1.0 - inter.obj->absorption));
}

t_clr			ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound)
{
	static t_vec3	view;

	view = sub_vec3(ray.pos, inter.pos);
	ray.pos = inter.pos;
	ray.dir = norm_vec3(sub_vec3(mul_vec3(inter.normal,
					2.0 * dot_vec3(inter.normal, view)), view));
	return (mul_clr(raytrace(core, ray, rebound), 1.0 - inter.obj->absorption));
}

t_clr			ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound)
{
	double	k;

	k = fresnel(ray, inter.pos, inter.normal, 1.5);
	return (add_clr(mul_clr(ray_trace_reflection(core, ray, inter, rebound), k),
				mul_clr(ray_trace_refraction(core, ray, inter, rebound),
					1.0 - k)));
}

t_clr			raytrace(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound)
{
	static t_clr	(*re_trace[3])(t_rtv1 const *, t_ray, t_inter const,
			unsigned int const) = {&ray_trace_reflection, &ray_trace_refraction,
		&ray_trace_fresnel};
	static t_inter	inter;
	t_clr			color_pxl;

	inter = get_inter(core, ray);
	if (inter.obj != NULL)
	{
		color_pxl = handle_color(core, inter.normal, inter.obj, inter.pos);
		if (inter.obj->mat != MATERIAL_DEFAULT && rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl, inter.obj->absorption),
					re_trace[inter.obj->mat](core, ray, inter, rebound - 1));
	}
	else
		return (new_clr(0.0, 0.0, 0.0, 0.0));
	return (color_pxl);
}
