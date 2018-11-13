/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/13 19:05:36 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

static t_ray	get_cam_dir(t_env const *e, t_vec3 const pos,
		double const x, double const y)
{
	static double const	half_h = WIN_H / 2;
	static double const	half_w = WIN_W / 2;
	t_ray	ray;

	ray.pos = pos;
	ray.dir.x = x - half_w;
	ray.dir.y = y - half_h;
	ray.dir.z = e->core.cam.ray.dir.z;
	ray.dir = rot_vec3(norm_vec3(ray.dir), e->core.cam.rotate);
	ray.dir = norm_vec3(ray.dir);
	return (ray);
}

static t_clr	handle_color(t_env const *e, t_vec3 const normal,
		t_poly const *obj, t_vec3 const inter)
{
	t_clr	color_pxl;

	color_pxl = phong_shading(&e->core, obj, normal, inter);
	color_pxl.r = (color_pxl.r > 1.0) ? 1.0 : color_pxl.r;
	color_pxl.g = (color_pxl.g > 1.0) ? 1.0 : color_pxl.g;
	color_pxl.b = (color_pxl.b > 1.0) ? 1.0 : color_pxl.b;
	return (color_pxl);
}

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

t_clr	raytrace(t_env const *e, t_ray ray, unsigned int depth);

static t_clr	ray_trace_reflection(t_env const *e, t_ray ray,
		t_vec3 const inter, t_vec3 const normal,
		double const absorbance, unsigned int const depth)
{
	t_clr	refl_clr;
	t_vec3	view;

	view = sub_vec3(ray.pos, inter);
	ray.pos = inter;
	ray.dir = norm_vec3(sub_vec3(mul_vec3(normal, 2.0 * dot_vec3(normal, view)),
				view));
	refl_clr = raytrace(e, ray, depth - 1);
	refl_clr = mul_clr(refl_clr, 1 - absorbance);
	return (refl_clr);
}

t_clr		raytrace(t_env const *e, t_ray ray, unsigned int const depth)
{
	t_clr			color_pxl;
	t_poly			*obj_near;
	t_vec3			inter;
	t_vec3			normal;
	double			distance;
	static double	absorbance = 0.40;

	if ((obj_near = get_nearest_obj(&e->core, ray, &distance)) != NULL)
	{
		inter = add_vec3(ray.pos, mul_vec3(ray.dir, distance));
		normal = e->core.normal_obj[obj_near->type](obj_near->data,
				(obj_near->type != TYPE_PLANE) ? inter : ray.dir);
		color_pxl = handle_color(e, normal, obj_near, inter);
		if (depth > 0)
		{
			color_pxl = mul_clr(color_pxl, absorbance);
			color_pxl = add_clr(color_pxl,
					ray_trace_reflection(e, ray, inter, normal, absorbance,
						depth));
		}
	}
	else
		color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	return (color_pxl);
}

t_clr			raytrace_alias(t_env *e, t_ray ray, int const x, int const y)
{
	static t_clr		color;
	static t_clr		tmp;
	static t_vec3		ray_pos;
	static t_aa			data;

	ray_pos = e->core.cam.ray.pos;
	data.n_ray = 0;
	data.y = -e->aa;
	color = new_clr(0.0, 0.0, 0.0, 0.0);
	while (data.y <= e->aa)
	{
		data.x = -e->aa + ((data.y < 0) ? -data.y : data.y);
		data.xlim = e->aa - ((data.y < 0) ? -data.y : data.y);
		while (data.x <= data.xlim)
		{
			ray = get_cam_dir(e, ray_pos, x + (data.x * e->core.offset_aa),
					y + (data.y * e->core.offset_aa));
			tmp = raytrace(e, ray, e->core.depth);
			tmp.r = ((tmp.r > 1.0) ? 1.0 : tmp.r) * 255.0;
			tmp.g = ((tmp.g > 1.0) ? 1.0 : tmp.g) * 255.0;
			tmp.b = ((tmp.b > 1.0) ? 1.0 : tmp.b) * 255.0;
			tmp.a = 0;
			color = add_clr(color, tmp);
			data.n_ray++;
			data.x++;
		}
		data.y++;
	}
	return (div_clr(color, data.n_ray));
}

void			projection(t_env *e)
{
	t_clr	pxl;
	int		x;
	int		y;

	e->core.depth = 4;
	y = 0;
	e->core.offset_aa = (0.40 * (e->aa * 0.66)) / e->aa;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			pxl = raytrace_alias(e, e->core.cam.ray, x, y);
			SDL_SetRenderDrawColor(e->render, pxl.r, pxl.g, pxl.b, pxl.a);
			SDL_RenderDrawPoint(e->render, x, y);
			x++;
		}
		y++;
	}
}
