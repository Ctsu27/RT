/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:27:42 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 14:26:18 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "rt_ts.h"

int		intersection_cylinder(t_ray const ray, t_cyl cyl, double *t);
int		intersection_cone(t_ray const ray, t_cone cone, double *t);
int		intersection_plane(t_ray const ray, t_plane plane, double *t);
int		intersection_sphere(t_ray const ray, t_sphere sphere, double *t);

t_vec3	normal_cylinder(t_vec3 pos, t_vec3 intersect);
t_vec3	normal_cone(t_vec3 pos, t_vec3 intersect, double r);
t_vec3	normal_plane(t_vec3 dir);
t_vec3	normal_sphere(t_vec3 pos, t_vec3 intersect);
t_vec3	reverse_normal(t_vec3 n);

double	norm(double value, double min, double max);
double	lerp(double value, double min, double max);
#endif
