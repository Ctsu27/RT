/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/27 15:04:04 by kehuang          ###   ########.fr       */
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

static t_clr	raytrace_alias(t_env *e, t_ray ray, int const x, int const y)
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

static t_clr	raytrace_default(t_env *e, t_ray ray, int const x, int const y)
{
	ray = get_cam_dir(e, ray.pos, x, y);
	return (lerp_clr(raytrace(&e->core, ray, e->core.cam.rebound)));
}

void			projection(t_env *e)
{
	t_clr	(*get_color)(t_env *, t_ray, int const, int const);
	t_clr	pxl;
	int		x;
	int		y;

	y = 0;
	e->core.offset_aa = (0.40 * (e->aa * 0.66)) / e->aa;
	get_color = (e->aa == 0) ? &raytrace_default : &raytrace_alias;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			pxl = get_color(e, e->core.cam.ray, x, y);
			SDL_SetRenderDrawColor(e->render, pxl.r, pxl.g, pxl.b, pxl.a);
			SDL_RenderDrawPoint(e->render, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(e->render);
}
