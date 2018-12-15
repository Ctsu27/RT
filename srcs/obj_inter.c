/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:07:52 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:29:52 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"
#include "math_vec3.h"

static int	solver_quadratic(double a, double b, double c, double *t)
{
	double	delta;
	double	dis[2];

	delta = b * b - 4.0 * a * c;
	if (delta < 0)
		return (0);
	delta = sqrt(delta);
	b = -b;
	a = a * 2.0;
	dis[0] = ((b + delta) / a);
	dis[1] = ((b - delta) / a);
	if (dis[0] < 0.01 && dis[1] < 0.01)
		return (0);
	*t = (dis[0] < dis[1]) ? dis[0] : dis[1];
	return (1);
}

int			intersection_sphere(t_ray const ray, void *obj, double *t)
{
	t_sphere	*sphere;
	t_vec3		oc;
	t_unknown	tmp;

	sphere = (t_sphere *)obj;
	oc = sub_vec3(ray.pos, sphere->pos);
	tmp.a = dot_vec3(ray.dir, ray.dir);
	tmp.b = 2.0 * dot_vec3(ray.dir, oc);
	tmp.c = dot_vec3(oc, oc) - sphere->radius * sphere->radius;
	return (solver_quadratic(tmp.a, tmp.b, tmp.c, t));
}

int			intersection_cylinder(t_ray const ray, void *obj, double *t)
{
	t_cyl		*cyl;
	t_vec3		oc;
	t_vec3		dir;
	t_unknown	tmp;

	cyl = (t_cyl *)obj;
	oc = sub_vec3(ray.pos, cyl->pos);
	oc = rot_vec3(oc, cyl->rot);
	dir = rot_vec3(ray.dir, cyl->rot);
	tmp.a = dir.x * dir.x + dir.z * dir.z;
	tmp.b = 2.0 * (dir.x * oc.x + dir.z * oc.z);
	tmp.c = (oc.x * oc.x + oc.z * oc.z) - cyl->radius * cyl->radius;
	return (solver_quadratic(tmp.a, tmp.b, tmp.c, t));
}

int			intersection_cone(t_ray const ray, void *obj, double *t)
{
	t_cone		*cone;
	t_vec3		oc;
	t_vec3		dir;
	t_unknown	tmp;
	double		pow_r;

	cone = (t_cone *)obj;
	oc = sub_vec3(ray.pos, cone->pos);
	oc = rot_vec3(oc, cone->rot);
	dir = rot_vec3(ray.dir, cone->rot);
	pow_r = cone->radius * cone->radius;
	tmp.a = dir.x * dir.x - pow_r * dir.y * dir.y + dir.z * dir.z;
	tmp.b = 2.0 * (dir.x * oc.x - pow_r * dir.y * oc.y + dir.z * oc.z);
	tmp.c = oc.x * oc.x - pow_r * oc.y * oc.y + oc.z * oc.z;
	return (solver_quadratic(tmp.a, tmp.b, tmp.c, t));
}

int			intersection_plane(t_ray const ray, void *obj, double *t)
{
	t_plane	*plane;
	double	div;

	plane = (t_plane *)obj;
	div = dot_vec3(plane->dir, ray.dir);
	if (div == 0)
		return (0);
	*t = dot_vec3(plane->dir, sub_vec3(plane->pos, ray.pos)) / div;
	if (*t <= 0.0)
		return (0);
	return (1);
}
