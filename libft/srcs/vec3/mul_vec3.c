/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mul_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:42:24 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/17 09:55:54 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	mul_vec3(t_vec3 const *a, double const b)
{
	return (new_vec3(a->x * b,
				a->y * b,
				a->z * b));
}
