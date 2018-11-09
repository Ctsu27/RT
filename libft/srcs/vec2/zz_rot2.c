/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zz_rot2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:01:13 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/17 10:07:07 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec2.h"

t_vec2	zz_rot2(t_vec2 const *a, double const rad)
{
	double	cosinus;
	double	sinus;

	cosinus = cos(rad);
	sinus = sin(rad);
	return (new_vec2(a->x * cosinus - a->y * sinus,
				a->x * sinus + a->y * cosinus));
}
