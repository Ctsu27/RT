/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:33:36 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:14:49 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

t_vec2	new_vec2(double const x, double const y);

t_vec2	add_vec2(t_vec2 const a, t_vec2 const b);
t_vec2	div_vec2(t_vec2 const a, double const b);
t_vec2	mul_vec2(t_vec2 const a, double const b);
t_vec2	sub_vec2(t_vec2 const a, t_vec2 const b);

double	dot_vec2(t_vec2 const a, t_vec2 const b);
t_vec2	norm_vec2(t_vec2 const a);

t_vec2	zz_rot2(t_vec2 const a, double const rad);
#endif
