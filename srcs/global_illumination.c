/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_illumination.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:57 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:29:24 by kehuang          ###   ########.fr       */
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

static void		init_raytrace_diffuse(t_rtv1 const *core, t_ray ray,
		t_inters *hits, t_clr *clr_pxl)
{
	*clr_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	hits->size = 0;
	hits->data = get_all_inter(core, ray, &(hits->size));
}

t_clr			raytrace_diffuse(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound)
{
	t_inters	hits;
	t_inter		*data;
	t_clr		color_pxl;

	init_raytrace_diffuse(core, ray, &hits, &color_pxl);
	if (hits.data != NULL && (data = (hits.data))->obj != NULL
			&& data->obj->mat != MATERIAL_DEFAULT)
	{
		color_pxl = get_diffuse_clr(core, data->obj, data->normal, data->pos);
		if (data->obj->mat == MATERIAL_TRANSPARENT)
			color_pxl = add_clr(mul_clr(color_pxl, 1 - data->obj->absorption),
					mul_clr(gi_get_color_transparent(core, ray, rebound, hits),
						data->obj->absorption));
		else if (data->obj->mat != MATERIAL_DEFAULT &&
				data->obj->mat != MATERIAL_ILLUMINATE && rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl, data->obj->absorption),
					core->gi_trace[data->obj->mat](core, ray, *data,
						rebound - 1));
		if (data->obj->mat != MATERIAL_ILLUMINATE)
			color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	}
	free(hits.data);
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
