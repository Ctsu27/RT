/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ts.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 11:52:51 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/06 10:43:51 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TS_H
# define RT_TS_H

# include "vec3.h"
# include "clr.h"

# define FALSE 0
# define TRUE 1

# define GI_OFF 0
# define GI_ON 1

# define TYPE_SPHERE 0
# define TYPE_CYLINDER 1
# define TYPE_CONE 2
# define TYPE_PLANE 3

# define MATERIAL_REFLECTIVE 0
# define MATERIAL_REFRACTIVE 1
# define MATERIAL_FRESNEL 2
# define MATERIAL_TRANSPARENT 3
# define MATERIAL_ILLUMINATE 4
# define MATERIAL_DEFAULT 5

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
	t_ray			ray;
	t_vec3			rotate;
	double			fov;
	unsigned int	rebound;
	unsigned int	sample_ray;
	int				filter;
	int				gi;
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
	t_clr			clr;
	t_clr			ambient;
	double			absorption;
	unsigned int	type;
	unsigned int	mat;
	struct s_poly	*next;
}				t_poly;

typedef struct	s_inter
{
	t_poly	*obj;
	t_vec3	pos;
	t_vec3	normal;
	double	t;
}				t_inter;

typedef struct	s_inters
{
	t_inter	*data;
	int		size;
}				t_inters;

typedef struct	s_rtv1
{
	t_light			*light;
	t_poly			*objs;
	t_cam			cam;
	t_clr			(*trace[3])(struct s_rtv1 const *, t_ray,
			t_inter const, unsigned int const);
	t_clr			(*gi_trace[3])(struct s_rtv1 const *, t_ray,
			t_inter const, unsigned int const);
	t_vec3			(*normal_obj[4])(void *, t_vec3);
	int				(*inter_obj[4])(t_ray const, void *, double *);
	double			distance;
	double			offset_aa;
	int				n_light;
	int				n_obj;
	unsigned long	mask;
}				t_rtv1;

/*
**	#==========================================================================#
**	#--------------------------------------------------------------------------#
**	#                                  UTILS                                   #
*/

t_clr			handle_color(t_rtv1 const *core, t_vec3 const normal,
		t_poly const *obj, t_vec3 const inter);

t_inter			*get_all_inter(t_rtv1 const *core, t_ray const ray, int *size);

double			fresnel(t_ray const ray, t_vec3 const inter,
		t_vec3 const normal, double const ior);

/*
**	#==========================================================================#
**	#--------------------------------------------------------------------------#
**	#                                   RAY                                    #
*/

t_clr			ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound);
t_clr			ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound);
t_clr			ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_inter const inter, unsigned int const rebound);
t_clr			raytrace(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound);

t_clr			gi_ray_trace_refraction(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound);
t_clr			gi_ray_trace_reflection(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound);
t_clr			gi_ray_trace_fresnel(t_rtv1 const *core, t_ray ray,
		t_inter const hit, unsigned int const rebound);
t_clr			glob_illum(t_rtv1 const *core,
		t_vec3 const normal, t_vec3 const inter);
t_clr			raytrace_diffuse(t_rtv1 const *core, t_ray ray,
		unsigned int const rebound);

/*
**	#==========================================================================#
**	#--------------------------------------------------------------------------#
**	#                               TRANSPARENT                                #
*/

t_clr			get_color_transparent(t_rtv1 const *core, t_ray ray,
		unsigned int const reb, t_inters const hits);
t_clr			gi_get_color_transparent(t_rtv1 const *core, t_ray ray,
		unsigned int const reb, t_inters const hits);

/*
**	#==========================================================================#
**	#--------------------------------------------------------------------------#
**	#                                 PARSER                                   #
*/

void			json_error(t_cur *fcur, int const err);
void			ft_atod(t_cur *fcur, char *str, double *val);

/*
**	#==========================================================================#
**	#--------------------------------------------------------------------------#
**	#                                 PHONG                                    #
*/

int				not_obstruct(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const inter, t_light const *light);
t_clr			diffuse_clr(t_clr const obj_clr, t_vec3 const obj_normal,
		t_vec3 const light_dir, double const ratio);
t_clr			phong_shading(t_rtv1 const *core, t_poly const *obj,
		t_vec3 const obj_normal, t_vec3 const inter);

#endif
