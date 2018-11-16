/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:09:49 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/16 11:40:45 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "math_vec3.h"

static void	init_light(t_rtv1 *core)
{
	t_light	*ptr;

	core->n_light = 0;
	ptr = core->light;
	while (ptr != NULL)
	{
		ptr->clr = div_clr(ptr->clr, 255.0);
		core->n_light++;
		ptr = ptr->next;
	}
	if (core->n_light == 0)
		core->n_light = 1;
}

static void	init_fct(t_rtv1 *core)
{
	core->inter_obj[0] = &intersection_sphere;
	core->inter_obj[1] = &intersection_cylinder;
	core->inter_obj[2] = &intersection_cone;
	core->inter_obj[3] = &intersection_plane;
	core->normal_obj[0] = &normal_sphere;
	core->normal_obj[1] = &normal_cylinder;
	core->normal_obj[2] = &normal_cone;
	core->normal_obj[3] = &normal_plane;
	core->re_trace[0] = &ray_trace_reflection;
	core->re_trace[1] = &ray_trace_refraction;
	core->re_trace[2] = &ray_trace_fresnel;
}

static void	init_obj_clr(t_poly const *objs, int const n_light)
{
	t_poly	*ptr;

	ptr = (t_poly *)objs;
	while (ptr != NULL)
	{
		ptr->clr = div_clr(ptr->clr, 255.0);
		ptr->clr = div_clr(ptr->clr, n_light);
		ptr->ambient = mul_clr(ptr->clr, 0.30);
		ptr->ambient.a = 0.0;
		ptr = ptr->next;
	}
}

int			init_env(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0x01);
	if ((e->win = SDL_CreateWindow("Rip Trigonometry",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					WIN_W, WIN_H,
					SDL_WINDOW_SHOWN)) == NULL)
		return (0x02);
	if ((e->render = SDL_CreateRenderer(e->win, -1,
					SDL_RENDERER_ACCELERATED)) == NULL)
		return (0x06);
	init_fct(&(e->core));
	init_light(&e->core);
	init_obj_clr(e->core.objs, e->core.n_light);
	e->core.cam.ray.dir.z = (WIN_W / 2)
		/ tan((e->core.cam.fov * M_PI / 180) / 2);
	e->aa = 1;
	e->on = TRUE;
	SDL_SetRenderDrawColor(e->render, 0, 0, 0, 0);
	SDL_RenderClear(e->render);
	SDL_RenderPresent(e->render);
	return (0);
}
