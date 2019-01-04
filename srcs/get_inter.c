/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:28:13 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/04 23:13:29 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "memoryft.h"

t_inter			get_inter(t_rtv1 const *core, t_ray const ray)
{
	t_inter	inter;
	t_poly	*ptr;
	double	t[2];

	ptr = core->objs;
	inter.obj = NULL;
	t[1] = 0xffffffff;
	while (ptr != NULL)
	{
		if (core->inter_obj[ptr->type](ray, ptr->data, &t[0]))
			if (t[0] > 0.01 && (inter.obj == NULL || t[0] < t[1]))
			{
				t[1] = t[0];
				inter.obj = ptr;
			}
		ptr = ptr->next;
	}
	if (inter.obj != NULL)
	{
		inter.pos = add_vec3(ray.pos, mul_vec3(ray.dir, t[1]));
		inter.normal = core->normal_obj[inter.obj->type](inter.obj->data,
				(inter.obj->type != TYPE_PLANE) ? inter.pos : ray.dir);
	}
	return (inter);
}
