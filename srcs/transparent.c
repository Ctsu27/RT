/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:46:42 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/10 15:27:50 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_clr	get_all_transparent(t_rtv1 const *core,
		t_inters const hits, int *i)
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

t_clr			get_color_transparent(t_rtv1 const *core, t_ray ray,
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
			return (core->trace[hits.data[i].obj->mat](core, ray,
				hits.data[i], reb - 1));
		}
		return (add_clr(mul_clr(n, 1 - hits.data[i - 1].obj->absorption),
					mul_clr(core->trace[hits.data[i].obj->mat](core, ray,
							hits.data[i], reb - 1),
						hits.data[i - 1].obj->absorption)));
	}
	return (next_obj_clr(core, hits, n, i));
}

t_clr			gi_get_color_transparent(t_rtv1 const *core, t_ray ray,
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
			return (core->gi_trace[hits.data[i].obj->mat](core, ray,
				hits.data[i], reb - 1));
		}
		return (add_clr(mul_clr(n, 1 - hits.data[i - 1].obj->absorption),
					mul_clr(core->gi_trace[hits.data[i].obj->mat](core, ray,
							hits.data[i], reb - 1),
						hits.data[i - 1].obj->absorption)));
	}
	return (next_obj_clr(core, hits, n, i));
}
