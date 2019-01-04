/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_illumination.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:57 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/03 18:26:26 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include "rt.h"

static t_clr	get_diffuse_clr(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const obj_normal, t_vec3 const inter)
{
	t_light	*light_ptr;
	t_vec3	light_dir;
	t_clr	pxl;

	light_ptr = core->light;
	pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	while (light_ptr != NULL)
	{
		if (not_obstruct(core, obj, inter, light_ptr))
		{
			light_dir = norm_vec3(sub_vec3(light_ptr->pos, inter));
			pxl = diffuse_clr(obj->clr, obj_normal, light_dir, 0.80);
		}
		light_ptr = light_ptr->next;
	}
	return (pxl);
}

t_clr			raytrace_diffuse(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound)
{
	t_inter		hit;
	t_clr		color_pxl;
	static t_clr	(*gi_trace[3])(t_rtv1 const *, t_ray, t_inter const,
			unsigned int const) = {
		&gi_ray_trace_reflection,
		&gi_ray_trace_refraction,
		&gi_ray_trace_fresnel
	};

	hit = get_inter(core, ray);
	if (hit.obj != NULL && hit.obj->mat != MATERIAL_DEFAULT)
	{
		color_pxl = get_diffuse_clr(core, hit.obj, hit.normal, hit.pos);
		if (hit.obj->mat != MATERIAL_DEFAULT &&
				hit.obj->mat != MATERIAL_ILLUMINATE && rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl, hit.obj->clr.a),
					gi_trace[hit.obj->mat](core, ray, hit, rebound - 1));
		if (hit.obj->mat != MATERIAL_ILLUMINATE)
			color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	}
	else
		return (new_clr(0.0, 0.0, 0.0, 0.0));
	return (color_pxl);
}

t_clr			glob_illum(t_rtv1 const *core,
		t_vec3 const normal, t_vec3 const inter)
{
	t_ray			ray;
	t_clr			pxl;
	unsigned int	rebound;
	unsigned int	sample_ray;
	unsigned int	n_iter;

	ray.pos = inter;
	sample_ray = core->cam.sample_ray;
	rebound = core->cam.rebound;
	pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	n_iter = 0;
	while (n_iter < sample_ray)
	{
		ray.dir = rot_vec3(normal, rnew_vec3());
		pxl = add_clr(pxl, mul_clr(raytrace_diffuse(core, ray, rebound),
					core->n_light));
		n_iter++;
	}
	return (div_clr(pxl, sample_ray));
}
