/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_ptr_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:36:13 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 11:06:06 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int.h"
#include <stdlib.h>

static void	take_vec_sphere(t_poly *obj, t_vec3 **ptr)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj->data;
	*ptr = (t_vec3 *)&sphere->pos;
}

static void	take_vec_cyl(t_rtv1 *core, t_poly *obj, t_vec3 **ptr)
{
	t_cone	*cone;

	cone = (t_cone *)obj->data;
	if (core->mask & (KEY_POS << 16))
		*ptr = (t_vec3 *)&cone->pos;
	else if (core->mask & (KEY_ROT << 16))
		*ptr = (t_vec3 *)&cone->rot;
}

static void	take_vec_plane(t_rtv1 *core, t_poly *obj, t_vec3 **ptr)
{
	t_plane	*plane;

	plane = (t_plane *)obj->data;
	if (core->mask & (KEY_POS << 16))
		*ptr = (t_vec3 *)&plane->pos;
	else if (core->mask & (KEY_NORMAL << 16))
		*ptr = (t_vec3 *)&plane->dir;
}

void		take_obj_vec(t_rtv1 *core, t_vec3 **ptr)
{
	t_poly	*obj;

	obj = core->objs;
	while (obj->next != NULL)
		obj = obj->next;
	if (core->mask & KEY_SPHERE)
		take_vec_sphere(obj, ptr);
	else if (core->mask & (KEY_CYLINDER | KEY_CONE))
		take_vec_cyl(core, obj, ptr);
	else
		take_vec_plane(core, obj, ptr);
}

void		take_light_pos(t_rtv1 *core, t_vec3 **ptr)
{
	t_light	*light;

	light = core->light;
	while (light->next != NULL)
		light = light->next;
	*ptr = &light->pos;
}
