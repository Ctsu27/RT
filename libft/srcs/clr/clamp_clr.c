/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_clr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:55:17 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/05 13:41:02 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clr.h"

t_clr	clamp_clr(t_clr const a, double const max)
{
	return (new_clr((a.r > max) ? max : a.r,
			(a.g > max) ? max : a.g,
			(a.b > max) ? max : a.b,
			(a.a > max) ? max : a.a));
}
