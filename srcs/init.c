/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:09:49 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 17:10:38 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "math_vec3.h"

static void	get_light_divisor(t_rtv1 *core)
{
	t_light	*ptr;

	core->n_light = 0;
	ptr = core->light;
	while (ptr != NULL)
	{
		core->n_light++;
		ptr = ptr->next;
	}
	if (core->n_light == 0)
		core->n_light = 1;
}

int			init_env(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0x01);
	if ((e->win = SDL_CreateWindow("Rip Trigonometry V1",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					WIN_W, WIN_H,
					SDL_WINDOW_SHOWN)) == NULL)
		return (0x02);
	if ((e->render = SDL_CreateRenderer(e->win, -1,
					SDL_RENDERER_ACCELERATED)) == NULL)
		return (0x06);
	e->core.inter_obj[0] = &intersection_sphere;
	e->core.inter_obj[1] = &intersection_cylinder;
	e->core.inter_obj[2] = &intersection_cone;
	e->core.inter_obj[3] = &intersection_plane;
	e->core.normal_obj[0] = &normal_sphere;
	e->core.normal_obj[1] = &normal_cylinder;
	e->core.normal_obj[2] = &normal_cone;
	e->core.normal_obj[3] = &normal_plane;
	get_light_divisor(&e->core);
	e->aa = 1;
	e->on = TRUE;
	SDL_SetRenderDrawColor(e->render, 0, 0, 0, 0);
	SDL_RenderClear(e->render);
	SDL_RenderPresent(e->render);
	return (0);
}
