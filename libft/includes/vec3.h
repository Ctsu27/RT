/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:33:56 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 19:11:07 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

t_vec3	new_vec3(double const x, double const y, double const z);

t_vec3	add_vec3(t_vec3 const a, t_vec3 const b);
t_vec3	div_vec3(t_vec3 const a, double const b);
t_vec3	mul_vec3(t_vec3 const a, double const b);
t_vec3	sub_vec3(t_vec3 const a, t_vec3 const b);

double	dot_vec3(t_vec3 const a, t_vec3 const b);
t_vec3	norm_vec3(t_vec3 const a);

t_vec3	xx_rot3(t_vec3 const a, double const rad);
t_vec3	yy_rot3(t_vec3 const a, double const rad);
t_vec3	zz_rot3(t_vec3 const a, double const rad);
t_vec3	rot_vec3(t_vec3 const a, t_vec3 const rad);
#endif
