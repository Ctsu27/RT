/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 17:10:57 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "math_vec3.h"
#include <math.h>

static void		get_cam_dir(t_cam *cam, double const x, double const y)
{
	static double const	half_h = WIN_H / 2;
	static double const	half_w = WIN_W / 2;

	cam->ray.dir.x = x - half_w;
	cam->ray.dir.y = y - half_h;
	cam->ray.dir.z = half_w / tan((cam->fov * M_PI / 180) / 2);
	cam->ray.dir = rotate_vec3(norm_vec3(cam->ray.dir), cam->rotate);
	cam->ray.dir = norm_vec3(cam->ray.dir);
}

static t_clr	handle_color(t_env *e, t_poly const *obj)
{
	static t_vec3	inter;
	static t_vec3	normal;
	static t_clr	color_pxl;

	inter = add_vec3(e->core.cam.ray.pos, coeff_vec3(e->core.cam.ray.dir,
				e->core.distance));
	normal = e->core.normal_obj[obj->type](obj->data,
			(obj->type != TYPE_PLANE) ? inter : e->core.cam.ray.dir);
	color_pxl = phong_shading(&e->core, obj, normal, inter);
	color_pxl.r = ((color_pxl.r > 1.0) ? 1.0 : color_pxl.r) * 255.0;
	color_pxl.g = ((color_pxl.g > 1.0) ? 1.0 : color_pxl.g) * 255.0;
	color_pxl.b = ((color_pxl.b > 1.0) ? 1.0 : color_pxl.b) * 255.0;
	return (color_pxl);
}

static t_poly	*get_nearest_obj(t_rtv1 *core)
{
	static t_poly	*ptr;
	static t_poly	*near;
	static double	tmp;

	ptr = core->objs;
	near = NULL;
	while (ptr != NULL)
	{
		if (core->inter_obj[ptr->type](core->cam.ray, (void *)ptr->data, &tmp))
		{
			if (near == NULL || tmp < core->distance)
			{
				core->distance = tmp;
				near = ptr;
			}
		}
		ptr = ptr->next;
	}
	return (near);
}

t_clr			raytrace_alias(t_env *e, int const x, int const y)
{
	static t_poly	*obj_near;
	static t_clr	color_pxl;
	static t_aa		data;

	data.n_ray = 0;
	data.step = (0.40 * (e->aa * 0.66)) / e->aa;
	color_pxl = (t_clr){.r = 0.0, .g = 0.0, .b = 0.0, .a = 0.0};
	data.y = -e->aa;
	while (data.y <= e->aa)
	{
		data.x = -e->aa + ((data.y < 0) ? -data.y : data.y);
		data.xlim = e->aa - ((data.y < 0) ? -data.y : data.y);
		while (data.x <= data.xlim)
		{
			get_cam_dir(&e->core.cam, x + (data.x * data.step),
					y + (data.y * data.step));
			if ((obj_near = get_nearest_obj(&e->core)) != NULL)
				color_pxl = add_clr(color_pxl, handle_color(e, obj_near));
			data.n_ray++;
			data.x++;
		}
		data.y++;
	}
	return (div_clr(color_pxl, data.n_ray));
}

void			projection(t_env *e)
{
	t_clr	pxl;
	int		x;
	int		y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			pxl = raytrace_alias(e, x, y);
			SDL_SetRenderDrawColor(e->render, pxl.r, pxl.g, pxl.b, pxl.a);
			SDL_RenderDrawPoint(e->render, x, y);
			x++;
		}
		y++;
	}
}
