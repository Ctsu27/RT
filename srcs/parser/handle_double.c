/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:57:59 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/15 16:59:43 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "parser_int.h"

static int	handle_obj_radius(t_rtv1 *core, double val)
{
	t_poly		*ptr;
	t_cone		*cone;
	t_sphere	*sph;

	if (val <= 0.0)
		return (-1);
	ptr = core->objs;
	while (ptr->next != NULL)
		ptr = ptr->next;
	if (core->mask & KEY_SPHERE)
	{
		sph = (t_sphere *)ptr->data;
		sph->radius = val;
	}
	else if (core->mask & (KEY_CYLINDER | KEY_CONE))
	{
		cone = (t_cone *)ptr->data;
		cone->radius = (core->mask & KEY_CONE) ? val * M_PI / 180 : val;
	}
	return (0);
}

static int	handle_obj_depth(t_rtv1 *core, double val)
{
	t_poly			*ptr;
	unsigned int	depth;

	if (val < 0)
		return (-1);
	if ((ptr = core->objs) != NULL)
	{
		depth = (unsigned int)(val + 0.5);
		while (ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->material == MATERIAL_DEFAULT)
			ptr->rebound = 0;
		else
			ptr->rebound = depth;
	}
	return (0);
}

int			handle_double(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	double		val;

	ft_atod(fcur, cfile, &val);
	if (core->mask & KEY_CAM)
	{
		if (val < 0.0 || val >= 180.0)
			return (-1);
		core->cam.fov = val;
	}
	else if (core->mask & (KEY_DEPTH << 16))
	{
		if (handle_obj_depth(core, val) == -1)
			return (-1);
	}
	else if (handle_obj_radius(core, val) == -1)
		return (-1);
	return (0);
}
