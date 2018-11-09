/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:45:26 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 11:26:27 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser_int.h"

static int	get_light_clr(t_light *head, t_cur *fcur, char *cfile)
{
	t_light	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	if (ft_atod_sep(fcur, &ptr->clr.r, cfile, 1) == -1
			|| ptr->clr.r < 0.0 || ptr->clr.r > 255.0)
		return (-1);
	if (ft_atod_sep(fcur, &ptr->clr.g, cfile, 1) == -1
			|| ptr->clr.g < 0.0 || ptr->clr.g > 255.0)
		return (-1);
	if (ft_atod_sep(fcur, &ptr->clr.b, cfile, 1) == -1
			|| ptr->clr.b < 0.0 || ptr->clr.b > 255.0)
		return (-1);
	if (ft_atod_sep(fcur, &ptr->clr.a, cfile, 0) == -1
			|| ptr->clr.a < 0.0 || ptr->clr.a > 255.0)
		return (-1);
	return (0);
}

static int	get_obj_clr(t_poly *head, t_cur *fcur, char *cfile)
{
	t_poly	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	if (ft_atod_sep(fcur, &ptr->clr.r, cfile, 1) == -1
			|| ptr->clr.r < 0.0 || ptr->clr.r > 255.0)
		return (-1);
	if (ft_atod_sep(fcur, &ptr->clr.g, cfile, 1) == -1
			|| ptr->clr.g < 0.0 || ptr->clr.g > 255.0)
		return (-1);
	if (ft_atod_sep(fcur, &ptr->clr.b, cfile, 1) == -1
		|| ptr->clr.b < 0.0 || ptr->clr.b > 255.0)
		return (-1);
	if (ft_atod_sep(fcur, &ptr->clr.a, cfile, 0) == -1
			|| ptr->clr.a < 0.0 || ptr->clr.a > 255.0)
		return (-1);
	return (0);
}

int			get_clr(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	if (core->mask & KEY_LIGHT)
	{
		if (get_light_clr(core->light, fcur, cfile) == -1)
			return (-1);
	}
	else
	{
		if (get_obj_clr(core->objs, fcur, cfile) == -1)
			return (-1);
	}
	return (0);
}
