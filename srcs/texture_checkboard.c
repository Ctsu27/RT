/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checkboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 23:12:09 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/16 23:57:55 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt_ts.h"

static void	get_final_pos(t_vec3 const hit_pos, t_vec3 const rot, int *pos)
{
	t_vec3	f;

	f = rot_vec3(hit_pos, rot);
	pos[0] = round(f.x / TEXTURE_PROCESS_SIZE);
	pos[1] = round(f.y / TEXTURE_PROCESS_SIZE);
	pos[2] = round(f.z / TEXTURE_PROCESS_SIZE);
}

t_clr		texture_checkboard(t_vec3 const hit_pos, t_vec3 const rot)
{
	static t_clr const	white = {1.0, 1.0, 1.0, 0.0};
	static t_clr const	black = {0.0, 0.0, 0.0, 0.0};
	int					pos[3];
	t_clr				c;

	get_final_pos(hit_pos, rot, pos);
	if (pos[0] % 2 == 0)
	{
		if ((pos[1] % 2 == 0 && pos[2] % 2 == 0)
				|| (pos[1] % 2 != 0 && pos[2] % 2 != 0))
			c = white;
		else
			c = black;
	}
	else
	{
		if ((pos[1] % 2 == 0 && pos[2] % 2 == 0)
				|| (pos[1] % 2 != 0 && pos[2] % 2 != 0))
			c = black;
		else
			c = white;
	}
	return (c);
}
