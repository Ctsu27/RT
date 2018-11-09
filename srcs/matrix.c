/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:23:40 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/02 13:11:40 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_ts.h"
#include <math.h>

static t_vec3	xx_rot(t_vec3 vec, double angle)
{
	t_vec3	rot_vec;

	rot_vec.x = vec.x;
	rot_vec.y = vec.y * cos(angle) - vec.z * sin(angle);
	rot_vec.z = vec.y * sin(angle) + vec.z * cos(angle);
	return (rot_vec);
}

static t_vec3	yy_rot(t_vec3 vec, double angle)
{
	t_vec3	rot_vec;

	rot_vec.x = vec.z * sin(angle) + vec.x * cos(angle);
	rot_vec.y = vec.y;
	rot_vec.z = vec.z * cos(angle) - vec.x * sin(angle);
	return (rot_vec);
}

static t_vec3	zz_rot(t_vec3 vec, double angle)
{
	t_vec3	rot_vec;

	rot_vec.x = vec.x * cos(angle) - vec.y * sin(angle);
	rot_vec.y = vec.x * sin(angle) + vec.y * cos(angle);
	rot_vec.z = vec.z;
	return (rot_vec);
}

t_vec3			rotate_vec3(t_vec3 vec, t_vec3 rotation)
{
	t_vec3	vec_rotated;

	vec_rotated = xx_rot(vec, rotation.x * M_PI / 180);
	vec_rotated = yy_rot(vec_rotated, rotation.y * M_PI / 180);
	vec_rotated = zz_rot(vec_rotated, rotation.z * M_PI / 180);
	return (vec_rotated);
}
