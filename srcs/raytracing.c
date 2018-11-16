/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:58:16 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/16 14:16:22 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_poly	*get_nearest_obj(t_rtv1 const *core, t_ray const ray,
		double *distance)
{
	static t_poly	*ptr;
	static t_poly	*near;
	static double	tmp;

	ptr = core->objs;
	near = NULL;
	while (ptr != NULL)
	{
		if (core->inter_obj[ptr->type](ray, ptr->data, &tmp))
		{
			if (tmp > 0.01 && (near == NULL || tmp < *distance))
			{
				*distance = tmp;
				near = ptr;
			}
		}
		ptr = ptr->next;
	}
	return (near);
}

t_clr	ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_vec3 const inter, t_vec3 const normal,
		double const absorbance, unsigned int const rebound)
{
	static t_vec3	view;
	static double	tmp[3];
	static double	ior = 1.5;

	view = sub_vec3(inter, ray.pos);
	tmp[0] = dot_vec3(normal, view);
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
	ray.pos = inter;
	ray.dir = norm_vec3(add_vec3(mul_vec3(normal, tmp[1]),
				mul_vec3(normal, tmp[1] * tmp[0] - sqrt(tmp[2]))));
	return (mul_clr(raytrace(core, ray, rebound), 1.0 - absorbance));
}

t_clr	ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_vec3 const inter, t_vec3 const normal,
		double const absorbance, unsigned int const rebound)
{
	static t_vec3	view;

	view = sub_vec3(ray.pos, inter);
	ray.pos = inter;
	ray.dir = norm_vec3(sub_vec3(mul_vec3(normal, 2.0 * dot_vec3(normal, view)),
				view));
	return (mul_clr(raytrace(core, ray, rebound), 1.0 - absorbance));
}

t_clr		ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_vec3 const inter, t_vec3 const normal,
		double const absorbance, unsigned int const rebound)
{
	double	kr;

	kr = fresnel(ray, inter, normal, 1.5);
	return (add_clr(mul_clr(ray_trace_reflection(core, ray, inter,
						normal, 1.0 - absorbance, rebound), kr),
				mul_clr(ray_trace_refraction(core, ray, inter,
						normal, 1.0 - absorbance, rebound), 1.0 - kr)));
}

t_clr		raytrace(t_rtv1 const *core, t_ray ray, unsigned int const rebound)
{
	static t_clr	(*re_trace[3])(t_rtv1 const *, t_ray, t_vec3 const,
			t_vec3 const, double const, unsigned int const) = {&ray_trace_reflection,
		&ray_trace_refraction, &ray_trace_fresnel};
	t_clr			color_pxl;
	t_poly			*obj_near;
	t_vec3			inter;
	t_vec3			normal;
	double			distance;
	static double	absorbance = 0.40;

	color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	if ((obj_near = get_nearest_obj(core, ray, &distance)) != NULL)
	{
		inter = add_vec3(ray.pos, mul_vec3(ray.dir, distance));
		normal = core->normal_obj[obj_near->type](obj_near->data,
				(obj_near->type != TYPE_PLANE) ? inter : ray.dir);
		color_pxl = handle_color(core, normal, obj_near, inter);
		if (obj_near->material != MATERIAL_DEFAULT && rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl, absorbance),
					re_trace[obj_near->material](core, ray, inter,
						normal, absorbance, rebound - 1));
	}
	return (color_pxl);
}
