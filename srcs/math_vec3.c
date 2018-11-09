/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:01:26 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 14:48:59 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt_ts.h"

t_vec3			add_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_vec3			coeff_vec3(t_vec3 vec, double coeff)
{
	t_vec3	new;

	new.x = vec.x * coeff;
	new.y = vec.y * coeff;
	new.z = vec.z * coeff;
	return (new);
}

double			dot_product(t_vec3 o, t_vec3 d)
{
	return (o.x * d.x + o.y * d.y + o.z * d.z);
}

t_vec3			sub_vec3(t_vec3 o, t_vec3 d)
{
	t_vec3	v;

	v.x = o.x - d.x;
	v.y = o.y - d.y;
	v.z = o.z - d.z;
	return (v);
}

t_vec3			norm_vec3(t_vec3 vec)
{
	t_vec3	pos;
	double	norm3;

	norm3 = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	pos.x = vec.x / norm3;
	pos.y = vec.y / norm3;
	pos.z = vec.z / norm3;
	return (pos);
}
