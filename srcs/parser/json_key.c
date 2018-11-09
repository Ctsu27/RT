/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:21:00 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 11:40:29 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_ts.h"
#include "parser_int.h"

static void	norm_mbenjell(int *ksize, char **keys)
{
	keys[0] = "\"plane\"";
	keys[1] = "\"cylinder\"";
	keys[2] = "\"cone\"";
	keys[3] = "\"sphere\"";
	keys[4] = "\"light\"";
	keys[5] = "\"cam\"";
	keys[6] = "\"normal\"";
	keys[7] = "\"radius\"";
	keys[8] = "\"color\"";
	keys[9] = "\"fov\"";
	keys[10] = "\"rot\"";
	keys[11] = "\"pos\"";
	ksize[0] = 7;
	ksize[1] = 10;
	ksize[2] = 6;
	ksize[3] = 8;
	ksize[4] = 7;
	ksize[5] = 5;
	ksize[6] = 8;
	ksize[7] = 8;
	ksize[8] = 7;
	ksize[9] = 5;
	ksize[10] = 5;
	ksize[11] = 5;
}

static int	mask_major(unsigned int *mask, int c)
{
	*mask = *mask | ((1 << c) << 8);
	*mask = *mask | MASK_OBJ;
	if (*mask & KEY_MAJOR)
		*mask = *mask | KEY_POS;
	if (*mask & KEY_CAM || *mask & KEY_CONE || *mask & KEY_CYLINDER)
		*mask = *mask | KEY_ROT;
	if (*mask & KEY_CAM)
		*mask = *mask | KEY_FOV;
	if (*mask & KEY_LIGHT || *mask & KEY_SPHERE || *mask & KEY_CONE
			|| *mask & KEY_CYLINDER || *mask & KEY_PLANE)
		*mask = *mask | KEY_COLOR;
	if (*mask & KEY_SPHERE || *mask & KEY_CONE || *mask & KEY_CYLINDER)
		*mask = *mask | KEY_RAD;
	if (*mask & KEY_PLANE)
		*mask = *mask | KEY_NORMAL;
	if (*mask & KEY_CAM && *mask & HAS_CAM)
		return (-1);
	if (*mask & KEY_CAM)
		*mask = *mask | HAS_CAM;
	return (0);
}

static int	mask_minor(t_rtv1 *core, int c)
{
	int		bit;

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

int			json_key(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	int		ksize[12];
	int		c;
	char	*keys[12];
	char	lim;

	norm_mbenjell(ksize, keys);
	c = (core->mask & KEY_MAJOR) ? 6 : 0;
	lim = (c == 6) ? 12 : 6;
	while (c < lim && ft_strncmp(keys[c], cfile + fcur->i, ksize[c]) != 0)
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
	fcur->i = fcur->i + ksize[c];
	fcur->x = fcur->x + ksize[c];
	return (0);
}
