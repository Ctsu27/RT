/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:11:57 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/02 10:11:58 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_ts.h"

t_clr	add_clr(t_clr const c1, t_clr const c2)
{
	t_clr	c3;

	c3.r = c1.r + c2.r;
	c3.g = c1.g + c2.g;
	c3.b = c1.b + c2.b;
	return (c3);
}

t_clr	div_clr(t_clr const c1, int const fac)
{
	t_clr	c2;

	c2.r = c1.r / fac;
	c2.g = c1.g / fac;
	c2.b = c1.b / fac;
	return (c2);
}
