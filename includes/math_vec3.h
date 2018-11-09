/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:25:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 15:11:45 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC3_H
# define MATH_VEC3_H
# include "rt_ts.h"

t_vec3	normal_sphere(void *data, t_vec3 intersect);
t_vec3	normal_cylinder(void *data, t_vec3 intersect);
t_vec3	normal_cone(void *data, t_vec3 intersect);
t_vec3	normal_plane(void *data, t_vec3 ray_dir);

int		intersection_plane(t_ray const ray, void *obj, double *t);
int		intersection_sphere(t_ray const ray, void *obj, double *t);
int		intersection_cylinder(t_ray const ray, void *obj, double *t);
int		intersection_cone(t_ray const ray, void *obj, double *t);

t_vec3	add_vec3(t_vec3 u, t_vec3 v);
t_vec3	coeff_vec3(t_vec3 vec, double coeff);
double	dot_product(t_vec3 o, t_vec3 d);
t_vec3	sub_vec3(t_vec3 o, t_vec3 d);
t_vec3	norm_vec3(t_vec3 vec);

t_vec3	rotate_vec3(t_vec3 vec, t_vec3 rotation);
#endif
