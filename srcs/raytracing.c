/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:58:16 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/30 12:40:29 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "memoryft.h"

static t_clr	(*g_trace[3])(t_rtv1 const *,
		t_ray,
		t_inter const,
		unsigned int const) = \
{
	&ray_trace_reflection,
	&ray_trace_refraction,
	&ray_trace_fresnel
};

static t_clr	get_all_transparent(t_rtv1 const *core, t_inters const hits,
		int *i)
{
	t_clr	n;

	n = new_clr(0.0, 0.0, 0.0, 0.0);
	while (*i < hits.size && hits.data[*i].obj->mat == MATERIAL_TRANSPARENT)
	{
		n = add_clr(n, mul_clr(handle_color(core, hits.data[*i].normal,
						hits.data[*i].obj, hits.data[*i].pos),
					hits.data[*i].obj->absorption));
		*i += 1;
	}
	return (div_clr(n, hits.size));
}

static t_clr	next_obj_clr(t_rtv1 const *core, t_inters const hits,
		t_clr const n, int const i)
{
	if (i == 1)
	{
		return (handle_color(core, hits.data[i].normal, hits.data[i].obj,
					hits.data[i].pos));
	}
	return (add_clr(mul_clr(n, 1 - hits.data[i - 1].obj->absorption),
				mul_clr(handle_color(core, hits.data[i].normal,
						hits.data[i].obj, hits.data[i].pos),
					hits.data[i - 1].obj->absorption)));
}

static t_clr	get_color_transparent(t_rtv1 const *core, t_ray ray,
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
			return (g_trace[hits.data[i].obj->mat](core, ray,
				hits.data[i], reb - 1));
		}
		return (add_clr(mul_clr(n, 1 - hits.data[i - 1].obj->absorption),
					mul_clr(g_trace[hits.data[i].obj->mat](core, ray,
							hits.data[i], reb - 1),
						hits.data[i - 1].obj->absorption)));
	}
	return (next_obj_clr(core, hits, n, i));
}

t_clr			raytrace(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound)
{
	t_inters		hits;
	t_clr			color_pxl;

	color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	hits.size = 0;
	hits.data = get_all_inter(core, ray, &hits.size);
	if (hits.data != NULL && (*(hits.data)).obj != NULL)
	{
		color_pxl = handle_color(core, (*(hits.data)).normal,
				(*(hits.data)).obj, (*(hits.data)).pos);
		if ((*(hits.data)).obj->mat == MATERIAL_TRANSPARENT)
			color_pxl = add_clr(mul_clr(color_pxl,
						1 - (*(hits.data)).obj->absorption),
					mul_clr(get_color_transparent(core, ray, rebound, hits),
						(*(hits.data)).obj->absorption));
		else if ((*(hits.data)).obj->mat != MATERIAL_DEFAULT && rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl,
						(*(hits.data)).obj->absorption),
					g_trace[(*(hits.data)).obj->mat](core, ray, (*(hits.data)),
						rebound - 1));
		free(hits.data);
	}
	return (color_pxl);
}
