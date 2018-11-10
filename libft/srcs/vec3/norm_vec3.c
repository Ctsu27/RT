/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:46:28 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:12:13 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"

t_vec3	norm_vec3(t_vec3 const a)
{
	return (div_vec3(a, sqrt(a.x * a.x + a.y * a.y + a.z * a.z)));
}
