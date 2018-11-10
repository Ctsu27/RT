/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xx_rot3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 09:39:00 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:13:48 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"

t_vec3	xx_rot3(t_vec3 const a, double const rad)
{
	double	cosinus;
	double	sinus;

	cosinus = cos(rad);
	sinus = sin(rad);
	return (new_vec3(a.x,
				a.y * cosinus - a.z * sinus,
				a.y * sinus + a.z * cosinus));
}
