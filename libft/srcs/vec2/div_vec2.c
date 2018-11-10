/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_vec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:40:19 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:15:02 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_vec2	div_vec2(t_vec2 const a, double const b)
{
	return (new_vec2(a.x / b,
				a.y / b));
}
