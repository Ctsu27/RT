/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_illumination.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:55:57 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/05 21:24:22 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "rt.h"

t_clr	(*g_gi_trace[3])(t_rtv1 const *,
		t_ray,
		t_inter const,
		unsigned int const) = \
{
	&gi_ray_trace_reflection,
	&gi_ray_trace_refraction,
	&gi_ray_trace_fresnel
};

static t_clr	get_diffuse_clr(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const obj_normal, t_vec3 const inter)
{
	static t_light	*light_ptr;
	static t_vec3	light_dir;
	static t_clr	pxl;

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

static t_clr	gi_get_color_transparent(t_rtv1 const *core, t_ray ray,
		unsigned int const reb, t_inters const hits)
{
	t_clr	n;
	int		i;

	if (hits.size == 0)
		return (new_clr(0.0, 0.0, 0.0, 0.0));
	i = 1;
	if (hits.data[i].obj->mat == MATERIAL_TRANSPARENT)
	{
		n = get_all_transparent(core, hits, &i);
		if (i == hits.size)
			return (mul_clr(n, hits.data[i - 1].obj->absorption));
	}
	if (hits.data[i].obj->mat != MATERIAL_DEFAULT && reb > 0)
	{
		if (i == 1)
		{
			return (g_gi_trace[hits.data[i].obj->mat](core, ray,
				hits.data[i], reb - 1));
		}
		return (add_clr(mul_clr(n, 1 - hits.data[i - 1].obj->absorption),
					mul_clr(g_gi_trace[hits.data[i].obj->mat](core, ray,
							hits.data[i], reb - 1),
						hits.data[i - 1].obj->absorption)));
	}
	return (next_obj_clr(core, hits, n, i));
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
	t_inters		hits;
	static t_inter	*data;
	t_clr			color_pxl;

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
					g_gi_trace[data->obj->mat](core, ray, *data, rebound - 1));
		if (data->obj->mat != MATERIAL_ILLUMINATE)
		{
			free(hits.data);
			color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
		}
	}
	return (color_pxl);
}

t_clr			glob_illum(t_rtv1 const *core,
		t_vec3 const normal, t_vec3 const inter)
{
	t_ray						ray;
	t_clr						pxl;
	t_clr						tmp;
	static unsigned int const	sample_ray = MAX_I;
	unsigned int				n_iter;

	ray.pos = inter;
	pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	n_iter = 0;
	while (n_iter < sample_ray)
	{
		ray.dir = rot_vec3(normal, rnew_vec3());
		tmp = raytrace_diffuse(core, ray, core->cam.rebound);
		pxl = add_clr(pxl, mul_clr(tmp, core->n_light));
		n_iter++;
	}
	return (div_clr(pxl, sample_ray));
}
