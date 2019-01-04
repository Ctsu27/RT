/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:09:49 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/04 23:02:44 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
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
}

static void	init_obj_clr(t_poly const *objs, int const n_light, int *n_obj)
{
	t_poly	*ptr;
	double	factor;

	ptr = (t_poly *)objs;
	while (ptr != NULL)
	{
		ptr->clr = div_clr(ptr->clr, 255.0);
		factor = ptr->clr.a;
		ptr->clr = div_clr(ptr->clr, n_light);
		ptr->clr.a = 1.0 - factor;
		ptr->ambient = mul_clr(ptr->clr, 0.30);
		ptr->ambient.a = 0.0;
		ptr = ptr->next;
		*n_obj += 1;
	}
}

int			init_env(t_env *e)
{
	int		useless[3];

	e->mlx = NULL;
	e->render = NULL;
	e->img = NULL;
	if ((e->mlx = mlx_init(e->mlx)) == NULL)
		return (0x1);
	if ((e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "Rip Teemo")) == NULL)
		return (0x2);
	if ((e->render = mlx_new_image(e->mlx, WIN_W, WIN_H)) == NULL)
		return (0x6);
	e->img = mlx_get_data_addr(e->render, useless, useless + 1, useless + 2);
	e->core.n_obj = 0;
	init_fct(&(e->core));
	init_light(&e->core);
	init_obj_clr(e->core.objs, e->core.n_light, &e->core.n_obj);
	e->core.cam.ray.dir.x = 0;
	e->core.cam.ray.dir.y = 0;
	e->core.cam.ray.dir.z = (WIN_W / 2)
		/ tan((e->core.cam.fov * M_PI / 180) / 2);
	e->aa = 0;
	e->on = TRUE;
	return (0);
}
