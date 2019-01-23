/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:58:16 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/18 21:42:58 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "memoryft.h"

t_clr			raytrace(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound)
{
	t_inter	hit;
	t_clr	color_pxl;
	static t_clr	(*trace[3])(t_rtv1 const *, t_ray, t_inter const,
			unsigned int const) = {
		&ray_trace_reflection,
		&ray_trace_refraction,
		&ray_trace_fresnel
	};

	color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	hit = get_inter(core, ray);
	if (hit.obj != NULL)
	{
		color_pxl = handle_color(core, hit, ray);
		if (hit.obj->mat != MATERIAL_DEFAULT
				&& hit.obj->mat != MATERIAL_ILLUMINATE && rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl, hit.obj->clr.a),
					trace[hit.obj->mat](core, ray, hit, rebound - 1));
	}
	return (color_pxl);
}
