/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:42:39 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:13:42 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	sub_vec3(t_vec3 const a, t_vec3 const b)
{
	return (new_vec3(a.x - b.x,
				a.y - b.y,
				a.z - b.z));
}
