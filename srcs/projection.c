/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/16 12:31:12 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
#include "ioft.h"

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

static t_clr	handle_color(t_rtv1 const *core, t_vec3 const normal,
		t_poly const *obj, t_vec3 const inter)
{
	t_clr	color_pxl;

	color_pxl = phong_shading(core, obj, normal, inter);
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

double	fresnel(t_ray const ray, t_vec3 const inter, t_vec3 const normal,
		double const ior)
{
	static t_vec3	view;
	static double	cos[2];
	static double	eta[2];
	static double	r[2];
	static double	sin_t;

	view = sub_vec3(inter, ray.pos);
	cos[0] = dot_vec3(normal, view);
	if (cos[0] < 0)
	{
		eta[0] = 1.0;
		eta[1] = ior;
	}
	else
	{
		eta[0] = ior;
		eta[1] = 1.0;
	}
	sin_t = (eta[0] / eta[1]) * fmax(0.0, 1.0 - cos[0] * cos[0]);
	if (sin_t >= 1.0)
		return (1.0);
	cos[1] = fmax(0.0, 1.0 - sin_t * sin_t);
	cos[0] = (cos[0] < 0.0) ? -cos[0] : cos[0];
	r[0] = (eta[1] * cos[0] - eta[0] * cos[1]) / (eta[1] * cos[0] + eta[0] * cos[1]);
	r[1] = (eta[0] * cos[0] - eta[1] * cos[1]) / (eta[0] * cos[0] + eta[1] * cos[1]);
	return ((r[0] * r[0] + r[1] * r[1]) / 2);
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
					core->re_trace[obj_near->material](core, ray, inter,
						normal, absorbance, rebound - 1));
	}
	return (color_pxl);
}

t_clr			raytrace_alias(t_env *e, t_ray ray, int const x, int const y)
{
	static t_clr		color;
	static t_vec3		ray_pos;
	static t_aa			data;
	static unsigned int	rebound;

	ray_pos = e->core.cam.ray.pos;
	data.n_ray = 0;
	data.y = -e->aa;
	color = new_clr(0.0, 0.0, 0.0, 0.0);
	rebound = e->core.cam.rebound;
	while (data.y <= e->aa)
	{
		data.x = -e->aa + ((data.y < 0) ? -data.y : data.y);
		data.xlim = e->aa - ((data.y < 0) ? -data.y : data.y);
		while (data.x <= data.xlim)
		{
			ray = get_cam_dir(e, ray_pos, x + (data.x * e->core.offset_aa),
					y + (data.y * e->core.offset_aa));
			color = add_clr(color, lerp_clr(raytrace(&e->core, ray, rebound)));
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
