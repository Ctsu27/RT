/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:05 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/10 14:49:42 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "math_vec3.h"
#include <math.h>

static int		not_obstruct(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const inter, t_light const *light)
{
	static t_ray	ray;
	static t_poly	*ptr;
	static t_vec3	vdis;
	static double	t;
	static double	distance_max;

	ray.pos = inter;
	vdis = sub_vec3(light->pos, ray.pos);
	ray.dir = norm_vec3(vdis);
	ptr = core->objs;
	distance_max = sqrt(vdis.x * vdis.x + vdis.y * vdis.y + vdis.z * vdis.z);
	while (ptr != NULL)
	{
		if (ptr != obj)
			if (core->inter_obj[ptr->type](ray, ptr->data, &t))
				if (t > 0.0 && t < distance_max)
					return (FALSE);
		ptr = ptr->next;
	}
	return (TRUE);
}

static t_clr	diffuse_clr(t_clr obj_clr, t_vec3 obj_normal,
		t_vec3 light_dir)
{
	static t_clr	diffuse;
	static double	factor_clr;

	factor_clr = dot_vec3(obj_normal, light_dir);
	if (factor_clr < 0.0)
	{
		diffuse.r = 0.0;
		diffuse.g = 0.0;
		diffuse.b = 0.0;
		diffuse.a = 255.0;
	}
	else
	{
		factor_clr = factor_clr * 0.70;
		diffuse.r = obj_clr.r * factor_clr;
		diffuse.g = obj_clr.g * factor_clr;
		diffuse.b = obj_clr.b * factor_clr;
		diffuse.a = 0.0;
	}
	return (diffuse);
}

static t_clr	specular_clr(t_vec3 const view, t_vec3 const light_dir,
		t_vec3 const obj_normal, t_clr const light_clr)
{
	static t_vec3		reflection;
	static t_clr		specul;
	static double		omega;
	static const int	alpha = 120;

	reflection = norm_vec3(sub_vec3(light_dir,
				mul_vec3(obj_normal, 2.0 * dot_vec3(obj_normal, light_dir))));
	omega = dot_vec3(reflection, view);
	if (omega > 0.0)
	{
		omega = pow(omega, alpha);
		specul.r = omega * (light_clr.r * 0.50);
		specul.g = omega * (light_clr.g * 0.50);
		specul.b = omega * (light_clr.b * 0.50);
		specul.a = 0.0;
	}
	else
	{
		specul.r = 0.0;
		specul.g = 0.0;
		specul.b = 0.0;
		specul.a = 255.0;
	}
	return (specul);
}

t_clr			phong_shading(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const obj_normal, t_vec3 const inter)
{
	static t_light	*light_ptr;
	static t_vec3	light_dir;
	static t_vec3	view;
	static t_clr	pxl;

	light_ptr = core->light;
	pxl = obj->ambient;
	while (light_ptr != NULL)
	{
		if (not_obstruct(core, obj, inter, light_ptr))
		{
			light_dir = norm_vec3(sub_vec3(inter, light_ptr->pos));
			pxl = add_clr(pxl, diffuse_clr(obj->clr, obj_normal, light_dir));
			view = norm_vec3(sub_vec3(core->cam.ray.pos, inter));
			pxl = add_clr(pxl,
					specular_clr(view, light_dir, obj_normal, light_ptr->clr));
		}
		light_ptr = light_ptr->next;
	}
	return (pxl);
}
