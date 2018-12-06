/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_json.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:16:49 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/06 15:09:22 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int.h"

/*
**	cam
**	light
**	sphere
**	cone
**	cylinder
**	plane
**
**	sample ray
**	global illumination
**	filter
**	absorption
**	depth
**	material
**	pos
**	rotation
**	fov
**	color
**	radius
**	normal
**	--  ---c --ao    ---- ----    ---- ----    --cl scyp
**	0b  0000 0000 |  0000 0000 |  0000 0000 |  0000 0000
**
**	--  ---- ---a    dmpr fcrn    ---- sgfa    dmpr fcrn
**	--  0000 0000 |  0000 0000 |  0000 0000 |  0000 0000
**
**	'o' bit --> '{' had to be encounter
**	'a' bit --> if object/light is allocated
**	'c' 0x10000000 bit --> if there's a cam encountered
*/

int			first_check_json(t_cur *fcur, int const fsize, char *cfile)
{
	int		j;

	j = fsize - 1;
	while (ft_iswhitespace(cfile[j]))
		j--;
	if (cfile[j] != '}')
	{
		free(cfile);
		json_error(NULL, 2);
	}
	ft_zjump(fcur, cfile);
	if (cfile[fcur->i] != '{')
	{
		free(cfile);
		json_error(fcur, 1);
	}
	fcur->i++;
	return (j);
}

/*
**	json set checks if between theres a ':' between key:value
*/

int			json_sep(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	(void)core;
	if (cfile[fcur->i] != ':')
		return (-1);
	fcur->i++;
	fcur->x++;
	return (0);
}

/*
**	json val must check if it ends with ',' or '}' depending to minor of major
*/

static void	init_json(t_rtv1 *core, int (**check)(t_rtv1 *, t_cur *, char *),
		t_cur *fcur, int *ch)
{
	check[0] = &json_key;
	check[1] = &json_sep;
	check[2] = &json_val;
	core->light = NULL;
	core->objs = NULL;
	core->mask = 0;
	fcur->x = 1;
	fcur->y = 1;
	*ch = 0;
	fcur->i = 0;
}

int			last_check_json(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	if (core->mask & MASK_STOP && cfile[fcur->i] != '}')
		return (8);
	if (cfile[fcur->i] != '}')
		return (6);
	if ((core->mask & HAS_CAM) == 0)
		return (7);
	if (core->mask & KEY_MINOR)
		return (9);
	return (0);
}

void		parser_json(t_rtv1 *core, int const fsize, char *cfile)
{
	int		(*check[3])(t_rtv1 *, t_cur *, char *);
	int		end;
	t_cur	fcur;
	int		ch;

	init_json(core, check, &fcur, &ch);
	end = first_check_json(&fcur, fsize, cfile);
	while (fcur.i < end && (core->mask & MASK_STOP) == 0)
	{
		ft_zjump(&fcur, cfile);
		if (check[ch](core, &fcur, cfile) == -1)
		{
			free(cfile);
			free_lst(core);
			json_error(&fcur, ch + 3);
		}
		if (++ch > 2)
			ch = 0;
	}
	if ((ch = last_check_json(core, &fcur, cfile)) != 0)
	{
		free(cfile);
		json_error((ch == 7) ? NULL : &fcur, ch);
	}
}
