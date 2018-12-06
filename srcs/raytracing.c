/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:58:16 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/06 10:26:37 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "memoryft.h"

t_clr			raytrace(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound)
{
	t_inters		hits;
	t_clr			color_pxl;

	color_pxl = new_clr(0.0, 0.0, 0.0, 0.0);
	hits.size = 0;
	hits.data = get_all_inter(core, ray, &hits.size);
	if (hits.data != NULL && (*(hits.data)).obj != NULL)
	{
		color_pxl = handle_color(core, (*(hits.data)).normal,
				(*(hits.data)).obj, (*(hits.data)).pos);
		if ((*(hits.data)).obj->mat == MATERIAL_TRANSPARENT)
			color_pxl = add_clr(mul_clr(color_pxl,
						1 - (*(hits.data)).obj->absorption),
					mul_clr(get_color_transparent(core, ray, rebound, hits),
						(*(hits.data)).obj->absorption));
		else if ((*(hits.data)).obj->mat != MATERIAL_DEFAULT
				&& (*(hits.data)).obj->mat != MATERIAL_ILLUMINATE
				&& rebound > 0)
			color_pxl = add_clr(mul_clr(color_pxl,
						(*(hits.data)).obj->absorption),
					core->trace[(*(hits.data)).obj->mat](core, ray,
						(*(hits.data)), rebound - 1));
		free(hits.data);
	}
	return (color_pxl);
}
