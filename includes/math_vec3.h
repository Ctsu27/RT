/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:25:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/09 18:43:47 by kehuang          ###   ########.fr       */
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

#endif
