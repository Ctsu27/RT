/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:21:00 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/26 11:04:35 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_ts.h"
#include "parser_int.h"

t_string		g_keys[KEY_MAX] = \
{
	[0] = {"\"plane\"", 7},
	[1] = {"\"cylinder\"", 10},
	[2] = {"\"cone\"", 6},
	[3] = {"\"sphere\"", 8},
	[4] = {"\"light\"", 7},
	[5] = {"\"cam\"", 5},
	[6] = {"\"normal\"", 8},
	[7] = {"\"radius\"", 8},
	[8] = {"\"color\"", 7},
	[9] = {"\"fov\"", 5},
	[10] = {"\"rot\"", 5},
	[11] = {"\"pos\"", 5},
	[12] = {"\"material\"", 10},
	[13] = {"\"depth\"", 7},
	[14] = {"\"absorption\"", 12}
};

static void		more_mask(unsigned long *mask)
{
	if (*mask & KEY_LIGHT || *mask & KEY_OBJECT)
		*mask = *mask | KEY_COLOR;
	if (*mask & KEY_SPHERE || *mask & KEY_CONE || *mask & KEY_CYLINDER)
		*mask = *mask | KEY_RAD;
	if (*mask & KEY_PLANE)
		*mask = *mask | KEY_NORMAL;
	if (*mask & KEY_OBJECT)
	{
		*mask = *mask | KEY_MATERIAL;
		*mask = *mask | KEY_ABSORPTION;
	}
}

static int		mask_major(unsigned long *mask, int c)
{
	*mask = *mask | (unsigned long)((unsigned long)(1 << c) << 32);
	*mask = *mask | MASK_OBJ;
	if (*mask & KEY_MAJOR)
		*mask = *mask | KEY_POS;
	if (*mask & KEY_CAM || *mask & KEY_CONE || *mask & KEY_CYLINDER)
		*mask = *mask | KEY_ROT;
	if (*mask & KEY_CAM)
	{
		*mask = *mask | KEY_FOV;
		*mask = *mask | KEY_DEPTH;
	}
	more_mask(mask);
	if (*mask & KEY_CAM && *mask & HAS_CAM)
		return (-1);
	if (*mask & KEY_CAM)
		*mask = *mask | HAS_CAM;
	return (0);
}

static int		mask_minor(t_rtv1 *core, int c)
{
	unsigned long	bit;

	bit = (1 << (c - 6));
	if (core->mask & bit)
	{
		core->mask = core->mask | (bit << 16);
		core->mask = core->mask ^ bit;
	}
	else
		return (-1);
	return (0);
}

int				json_key(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	int		c;
	char	lim;

	c = (core->mask & KEY_MAJOR) ? 6 : 0;
	lim = (c == 6) ? KEY_MAX : 6;
	while (c < lim
			&& ft_strncmp(g_keys[c].str, cfile + fcur->i, g_keys[c].size) != 0)
		c++;
	if (c == lim)
		return (-1);
	if (lim == 6)
	{
		if (mask_major(&core->mask, c) == -1)
			return (-1);
		if (core->mask & (KEY_LIGHT | KEY_OBJS))
			alloc_lst(core);
	}
	else if (mask_minor(core, c) == -1)
		return (-1);
	fcur->i = fcur->i + g_keys[c].size;
	fcur->x = fcur->x + g_keys[c].size;
	return (0);
}
