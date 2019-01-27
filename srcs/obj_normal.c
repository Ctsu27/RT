/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:01:33 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/27 15:11:08 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"
#include "math_vec3.h"

t_vec3			normal_cylinder(void *data, t_vec3 intersect)
{
	t_cyl	*cyl;
	t_vec3	normal;
	t_vec3	tmp;

	cyl = (t_cyl *)data;
	normal = rot_vec3(sub_vec3(intersect, cyl->pos), cyl->rot);
	normal.y = 0;
	tmp.x = 360 - cyl->rot.x;
	tmp.y = 360 - cyl->rot.y;
	tmp.z = 360 - cyl->rot.z;
	normal = norm_vec3(rot_vec3(normal, tmp));
	return (normal);
}

t_vec3			normal_cone(void *data, t_vec3 intersect)
{
	t_cone	*cone;
	t_vec3	normal;
	t_vec3	tmp;

	cone = (t_cone *)data;
	normal = rot_vec3(sub_vec3(intersect, cone->pos), cone->rot);
	normal.y = -normal.y * tan(cone->radius * cone->radius);
	tmp.x = 360 - cone->rot.x;
	tmp.y = 360 - cone->rot.y;
	tmp.z = 360 - cone->rot.z;
	normal = norm_vec3(rot_vec3(normal, tmp));
	return (normal);
}

t_vec3			normal_plane(void *data, t_vec3 ray_dir)
{
	t_plane	*plane;
	t_vec3	normal;

	plane = (t_plane *)data;
	if (dot_vec3(ray_dir, plane->dir) > 0.0)
		plane->dir = mul_vec3(plane->dir, -1);
	normal = norm_vec3(plane->dir);
	return (normal);
}

t_vec3			normal_sphere(void *data, t_vec3 intersect)
{
	return (norm_vec3(sub_vec3(intersect, ((t_sphere *)data)->pos)));
}
