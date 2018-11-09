/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_obj_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:11:50 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/02 10:11:51 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int.h"

static int	treat_major_sep(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	if (cfile[fcur->i] != '}')
		return (-1);
	else
	{
		fcur->i++;
		fcur->x++;
	}
	core->mask = core->mask & 0xf0000000;
	ft_zjump(fcur, cfile);
	if (cfile[fcur->i] != ',')
		core->mask = core->mask | MASK_STOP;
	else
	{
		fcur->i++;
		fcur->x++;
	}
	return (0);
}

int			check_sep_val(t_rtv1 *core, t_cur *fcur, char *cfile)
{
	ft_zjump(fcur, cfile);
	if (core->mask & KEY_MINOR)
	{
		if (cfile[fcur->i] != ',')
			return (-1);
		else
		{
			fcur->i++;
			fcur->x++;
		}
	}
	else if (treat_major_sep(core, fcur, cfile) == -1)
		return (-1);
	return (0);
}

int			ft_atod_sep(t_cur *fcur, double *val, char *cfile, char check)
{
	ft_zjump(fcur, cfile);
	ft_atod(fcur, cfile, val);
	ft_zjump(fcur, cfile);
	if (check != 0)
	{
		if (cfile[fcur->i] != ',')
			return (-1);
		fcur->i++;
		fcur->x++;
	}
	return (0);
}
