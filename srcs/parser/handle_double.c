/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:57:59 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/03 18:12:36 by kehuang          ###   ########.fr       */
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

static int	handle_obj_ior(t_rtv1 *core, double const val)
{
	t_poly		*ptr;

	if (val < 1.0 || val > 1.8)
		return (-1);
	ptr = core->objs;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->ior = val;
	return (0);
}

static int	more_handle_double(t_rtv1 *core, double const val)
{
	if (core->mask & (KEY_SAMPLE_RAY << 16))
	{
		if (val < 1.0 || (int)(val + 0.5) > SAMPLE_MAX)
			return (-1);
		core->cam.sample_ray = (unsigned int)(val + 0.5);
	}
	else if (handle_obj_radius(core, val) == -1)
		return (-1);
	return (0);
}

int			handle_double(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	double		val;

	ft_atod(fcur, cfile, &val);
	if (core->mask & KEY_CAM && core->mask & (KEY_FOV << 16))
	{
		if (val < 0.0 || val >= 180.0)
			return (-1);
		core->cam.fov = val;
	}
	else if (core->mask & (KEY_DEPTH << 16))
	{
		if (val < 0 || (int)(val + 0.5) > REBOUND_MAX)
			return (-1);
		core->cam.rebound = (unsigned int)(val + 0.5);
	}
	else if (core->mask & (KEY_IOR << 16))
	{
		if (handle_obj_ior(core, val) == -1)
			return (-1);
	}
	else if (more_handle_double(core, val) == -1)
		return (-1);
	return (0);
}
