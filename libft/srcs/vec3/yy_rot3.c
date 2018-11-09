/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yy_rot3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 09:39:02 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/17 09:51:03 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"

t_vec3	yy_rot3(t_vec3 const *a, double const rad)
{
	double	cosinus;
	double	sinus;

	cosinus = cos(rad);
	sinus = sin(rad);
	return (new_vec3(a->z * sinus + a->x * cosinus,
				a->y,
				a->z * cosinus - a->x * sinus));
}
