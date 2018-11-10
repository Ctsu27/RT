/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_vec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:02:35 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:15:08 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

double	dot_vec2(t_vec2 const a, t_vec2 const b)
{
	return (a.x * b.x + a.y * b.y);
}
