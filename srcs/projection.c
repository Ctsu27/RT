/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/12 17:22:45 by kehuang          ###   ########.fr       */
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

static t_clr	handle_color(t_env const *e, t_ray const ray,
		t_poly const *obj, t_vec3 const inter)
{
	t_vec3	normal;
	t_clr	color_pxl;

	normal = e->core.normal_obj[obj->type](obj->data,
			(obj->type != TYPE_PLANE) ? inter : ray.dir);
	color_pxl = phong_shading(&e->core, obj, normal, inter);
	color_pxl.r = ((color_pxl.r > 1.0) ? 1.0 : color_pxl.r) * 255.0;
	color_pxl.g = ((color_pxl.g > 1.0) ? 1.0 : color_pxl.g) * 255.0;
	color_pxl.b = ((color_pxl.b > 1.0) ? 1.0 : color_pxl.b) * 255.0;
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
			if (near == NULL || tmp < *distance)
			{
				*distance = tmp;
				near = ptr;
			}
		}
		ptr = ptr->next;
	}
	return (near);
}

static t_clr	raytrace(t_env const *e, t_ray const ray)
{
	t_clr	color_pxl;
	t_poly	*obj_near;
	t_vec3	inter;
	double	distance;

	if ((obj_near = get_nearest_obj(&e->core, ray, &distance)) != NULL)
	{
		inter = add_vec3(ray.pos, mul_vec3(ray.dir, distance));
		color_pxl = handle_color(e, ray, obj_near, inter);
	}
	else
		color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	return (color_pxl);
}

t_clr			raytrace_alias(t_env const *e, t_ray ray,
		int const x, int const y)
{
	t_clr	color;
	t_vec3	ray_pos;
	t_aa	data;
	double	offset;

	ray_pos = e->core.cam.ray.pos;
	offset = e->core.offset_aa;
	data.n_ray = 0;
	data.y = -e->aa;
	color = new_clr(0.0, 0.0, 0.0, 0.0);
	while (data.y <= e->aa)
	{
		data.x = -e->aa + ((data.y < 0) ? -data.y : data.y);
		data.xlim = e->aa - ((data.y < 0) ? -data.y : data.y);
		while (data.x <= data.xlim)
		{
			ray = get_cam_dir(e, ray_pos,
					x + (data.x * offset), y + (data.y * offset));
			color = add_clr(color, raytrace(e, ray));
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
