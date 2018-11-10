/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:54:12 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:13:04 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"

t_vec3	rot_vec3(t_vec3 const a, t_vec3 const deg)
{
	t_vec3	r;
	t_vec3	rad;

	rad = mul_vec3(deg, M_PI / 180.0);
	r = xx_rot3(a, rad.x);
	r = yy_rot3(r, rad.y);
	r = zz_rot3(r, rad.z);
	return (r);
}
