/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_clr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:51:40 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:19:08 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clr.h"

t_clr			new_clr(double const r,
		double const g,
		double const b,
		double const a)
{
	t_clr	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}
