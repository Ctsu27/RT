/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:25:16 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/04 23:09:38 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "strft.h"
#include "parser_int.h"

char	*g_str_value[3][6] = \
{
	[ID_MATERIAL] = \
	{
		"reflective",
		"refractive",
		"fresnel",
		"illuminate",
		"default",
		NULL
	}
	,
	[ID_FILTER] = \
	{
		"sepia",
		"gray",
		"deuteranomaly",
		"none",
		NULL
	}
	,
	[ID_GI] = \
	{
		"off",
		"on",
		NULL
	}
};

static void	get_obj_material(t_rtv1 *core, unsigned int const type)
{
	t_poly	*ptr;

	if ((ptr = core->objs) != NULL)
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->mat = type;
	}
}

static int	get_value_from_str(t_rtv1 *core, unsigned int const idx,
		unsigned long const key)
{
	if (key == ID_MATERIAL)
		get_obj_material(core, idx);
	else if (key == ID_FILTER)
		core->cam.filter = idx;
	else if (key == ID_GI)
		core->cam.gi = idx;
	else
		return (-1);
	return (0);
}

int			handle_str(t_rtv1 *core, t_cur *fcur,
		char *cfile, unsigned long key)
{
	unsigned int	size;
	unsigned int	idx;

	if (cfile[fcur->i] != '"')
		return (-1);
	fcur->i++;
	fcur->x++;
	if (key == KEY_MATERIAL)
		key = ID_MATERIAL;
	else if (key == KEY_FILTER)
		key = ID_FILTER;
	else if (key == KEY_GI)
		key = ID_GI;
	else
		return (-1);
	idx = 0;
	while (g_str_value[key][idx] != NULL
			&& ft_strncmp(g_str_value[key][idx], cfile + fcur->i,
				(size = ft_strlen(g_str_value[key][idx]))) != 0)
		idx++;
	if (g_str_value[key][idx] == NULL || cfile[fcur->i + size] != '"')
		return (-1);
	fcur->i = fcur->i + size + 1;
	fcur->x = fcur->x + size + 1;
	return (get_value_from_str(core, idx, key));
}
