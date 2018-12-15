/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:05 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:30:19 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "math_vec3.h"
#include <math.h>

extern unsigned int	g_state;

int				not_obstruct(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const inter, t_light const *light)
{
	t_ray	ray;
	t_poly	*ptr;
	t_vec3	vdis;
	double	t;
	double	distance_max;

	ray.pos = inter;
	vdis = sub_vec3(light->pos, ray.pos);
	ray.dir = norm_vec3(vdis);
	ptr = core->objs;
	distance_max = sqrt(vdis.x * vdis.x + vdis.y * vdis.y + vdis.z * vdis.z);
	while (ptr != NULL)
	{
		if (ptr != obj)
			if (core->inter_obj[ptr->type](ray, ptr->data, &t))
				if (t > 0.01 && t < distance_max)
					return (FALSE);
		ptr = ptr->next;
	}
	return (TRUE);
}

t_clr			diffuse_clr(t_clr const obj_clr, t_vec3 const obj_normal,
		t_vec3 const light_dir, double const ratio)
{
	double	factor_clr;

	factor_clr = dot_vec3(obj_normal, light_dir);
	if (factor_clr < 0.0)
		return (new_clr(0.0, 0.0, 0.0, 0.0));
	factor_clr = factor_clr * ratio;
	return (new_clr(obj_clr.r * factor_clr,
				obj_clr.g * factor_clr,
				obj_clr.b * factor_clr,
				0.0));
}

static t_clr	specular_clr(t_vec3 const view, t_vec3 const light_dir,
		t_vec3 const obj_normal, t_clr const light_clr)
{
	t_vec3		reflection;
	double		omega;
	static const int	alpha = 120;

	reflection = norm_vec3(sub_vec3(light_dir,
				mul_vec3(obj_normal, 2.0 * dot_vec3(obj_normal, light_dir))));
	omega = dot_vec3(reflection, view);
	if (omega <= 0.0)
		return (new_clr(0.0, 0.0, 0.0, 0.0));
	omega = pow(omega, alpha) * 0.50;
	return (new_clr(omega * light_clr.r,
				omega * light_clr.g,
				omega * light_clr.b,
				0.0));
}

t_clr			phong_shading(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const obj_normal, t_vec3 const inter)
{
	t_light	*light_ptr;
	t_vec3	light_dir;
	t_vec3	view;
	t_clr	pxl;

	light_ptr = core->light;
	pxl = obj->ambient;
	if (g_state == 1)
		while (light_ptr != NULL)
		{
			if (not_obstruct(core, obj, inter, light_ptr))
			{
				light_dir = norm_vec3(sub_vec3(light_ptr->pos, inter));
				pxl = add_clr(pxl, diffuse_clr(obj->clr, obj_normal,
							light_dir, 0.70));
				view = norm_vec3(sub_vec3(inter, core->cam.ray.pos));
				pxl = add_clr(pxl,
						specular_clr(view, light_dir,
							obj_normal, light_ptr->clr));
			}
			light_ptr = light_ptr->next;
		}
	return (pxl);
}

t_clr			handle_color(t_rtv1 const *core, t_vec3 const normal,
		t_poly const *obj, t_vec3 const inter)
{
	t_clr	color_pxl;

	color_pxl = phong_shading(core, obj, normal, inter);
	color_pxl = clamp_clr(color_pxl, 1.0);
	if (g_state == 1)
		if (core->cam.gi != GI_OFF)
			color_pxl = add_clr(color_pxl,
					clamp_clr(glob_illum(core, normal, inter), 1.0));
	return (color_pxl);
}
