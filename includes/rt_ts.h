/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ts.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 11:52:51 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/15 15:59:32 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TS_H
# define RT_TS_H

# include "vec3.h"
# include "clr.h"

# define FALSE 0
# define TRUE 1

# define TYPE_SPHERE 0
# define TYPE_CYLINDER 1
# define TYPE_CONE 2
# define TYPE_PLANE 3

# define MATERIAL_DEFAULT 0
# define MATERIAL_REFLECTIVE 1
# define MATERIAL_REFRACTIVE 2

typedef struct	s_aa
{
	int		n_ray;
	int		x;
	int		y;
	int		xlim;
}				t_aa;

typedef struct	s_unknown
{
	double	a;
	double	b;
	double	c;
}				t_unknown;

typedef struct	s_cur
{
	int		x;
	int		y;
	int		i;
}				t_cur;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}				t_ray;

typedef struct	s_plane
{
	t_vec3	pos;
	t_vec3	dir;
}				t_plane;

typedef struct	s_sphere
{
	t_vec3	pos;
	double	radius;
}				t_sphere;

typedef struct	s_cone
{
	t_vec3	pos;
	t_vec3	rot;
	double	radius;
}				t_cone;

typedef struct s_cone	t_cyl;

typedef struct	s_cam
{
	t_ray	ray;
	t_vec3	rotate;
	double	fov;
}				t_cam;

typedef struct	s_light
{
	t_vec3			pos;
	t_clr			clr;
	struct s_light	*next;
}				t_light;

typedef struct	s_poly
{
	void			*data;
	unsigned int	type;
	unsigned int	material;
	unsigned int	rebound;
	t_clr			clr;
	t_clr			ambient;
	struct s_poly	*next;
}				t_poly;

typedef struct	s_rtv1
{
	t_light			*light;
	t_poly			*objs;
	t_cam			cam;
	t_vec3			(*normal_obj[4])(void *, t_vec3);
	int				(*inter_obj[4])(t_ray const, void *, double *);
	double			distance;
	double			offset_aa;
	int				n_light;
	unsigned int	mask;
	unsigned int	depth;
}				t_rtv1;

void			json_error(t_cur *fcur, int const err);
void			ft_atod(t_cur *fcur, char *str, double *val);
t_clr			phong_shading(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const obj_normal, t_vec3 const inter);

#endif
