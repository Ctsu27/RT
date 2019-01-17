/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checkboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 23:12:09 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/17 14:31:31 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt_ts.h"

t_clr				texture_checkboard(t_vec3 const hit_pos,
		t_vec3 const rot,
		t_vec3 const offs,
		t_vec3 const size)
{
	static t_clr const	c[2] = {{1.0, 1.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 0.0}};
	t_vec3				f;
	int					pos[3];

	f = rot_vec3(hit_pos, rot);
	pos[0] = ((long long)(round((f.x + offs.x) / size.x)) & 0x1);
	pos[1] = ((long long)(round((f.y + offs.y) / size.y)) & 0x1);
	pos[2] = ((long long)(round((f.z + offs.z) / size.z)) & 0x1);
	return (c[pos[0] ^ pos[1] ^ pos[2]]);
}
