/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:12:44 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/31 21:35:03 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <math.h>
#include "libft.h"
#include "rt.h"
#include "mlx.h"

static t_ray	get_cam_dir(t_env const *e, t_vec3 const pos,
		double const x, double const y)
{
	static double const	half_h = WIN_H / 2;
	static double const	half_w = WIN_W / 2;
	t_ray				ray;

	ray.pos = pos;
	ray.dir.x = x - half_w;
	ray.dir.y = y - half_h;
	ray.dir.z = e->core.cam.ray.dir.z;
	ray.dir = rot_vec3(norm_vec3(ray.dir), e->core.cam.rotate);
	ray.dir = norm_vec3(ray.dir);
	return (ray);
}

static t_clr	raytrace_alias(t_env *e, t_ray ray, int const x, int const y)
{
	t_clr			color;
	t_vec3			ray_pos;
	t_aa			data;
	unsigned int	rebound;

	ray_pos = e->core.cam.ray.pos;
	data.n_ray = 0;
	data.y = -e->aa;
	color = new_clr(0.0, 0.0, 0.0, 0.0);
	rebound = e->core.cam.rebound;
	while (data.y <= e->aa)
	{
		data.x = -e->aa + ((data.y < 0) ? -data.y : data.y);
		data.xlim = e->aa - ((data.y < 0) ? -data.y : data.y);
		while (data.x <= data.xlim)
		{
			ray = get_cam_dir(e, ray_pos, x + (data.x * e->core.offset_aa),
					y + (data.y * e->core.offset_aa));
			color = add_clr(color, lerp_clr(raytrace(&e->core, ray, rebound)));
			data.n_ray++;
			data.x++;
		}
		data.y++;
	}
	return (div_clr(color, data.n_ray));
}

static t_clr	raytrace_default(t_env *e, t_ray ray, int const x, int const y)
{
	ray = get_cam_dir(e, ray.pos, x, y);
	return (lerp_clr(raytrace(&e->core, ray, e->core.cam.rebound)));
}

static void		draw_render(t_thread *th)
{
	t_clr	(*get_color)(t_env *, t_ray, int const, int const);
	t_clr	pxl;
	int		filter;
	int		x;
	int		y;

	filter = th->e->core.cam.filter;
	y = th->id;
	th->e->core.offset_aa = (0.40 * (th->e->aa * 0.66)) / th->e->aa;
	get_color = (th->e->aa == 0) ? &raytrace_default : &raytrace_alias;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			pxl = get_color(th->e, th->e->core.cam.ray, x, y);
			pxl = modifier_clr(pxl, filter);
			mlx_put_pxl_img(th->e->img, pxl, x, y);
			x++;
		}
		y += N_THREAD;
	}
	pthread_exit(NULL);
}

void		draw_edge(t_env const *e)
{
	t_clr			avg[9];
	t_clr			v_avg;
	t_clr			h_avg;
	t_clr			pxl;
	double const 	v_cvt[9] = {
		-1.0, 0.0, 1.0,
		-2.0, 0.0, 2.0,
		-1.0, 0.0, 1.0
	};
	double const 	h_cvt[9] = {
		-1.0, -2.0, -1.0,
		0.0, 0.0, 0.0,
		1.0, 2.0, 1.0
	};
	int				x;
	int				y;
	int				i;
	int				idx;

	ft_memset(e->ly_img, 255, (WIN_W * 4) * WIN_H);
	y = 1;
	while (y < WIN_H - 1)
	{
		x = 1;
		while (x < WIN_W - 1)
		{
//			get grayscale on the 3x3 on the cursor
			i = 0;
			while (i < 9)
			{
				idx = ((y - 1 + i % 3) * WIN_W * 4) + (((x - 1) * 4) + i % 3);
				avg[i].b = e->img[idx];
				avg[i].g = e->img[idx + 1];
				avg[i].r = e->img[idx + 2];
				avg[i].a = 0.0;
				avg[i] = modifier_clr(avg[i], FILTER_GRAY);
				++i;
			}
//			use the vertical sobel edge detection avec the kernel convulusion
			v_avg = new_clr(0.0, 0.0, 0.0, 0.0);
			i = 0;
			while (i < 9)
			{
				v_avg = add_clr(v_avg, mul_clr(avg[i], v_cvt[i]));
				++i;
			}
			v_avg = div_clr(v_avg, 9.0);
//			use the horizontal sobel edge detection avec the kernel convulusion
			h_avg = new_clr(0.0, 0.0, 0.0, 0.0);
			i = 0;
			while (i < 9)
			{
				h_avg = add_clr(h_avg, mul_clr(avg[i], h_cvt[i]));
				++i;
			}
			h_avg = div_clr(h_avg, 9.0);
			pxl = new_clr(sqrt((pow(v_avg.r, 2.0) + pow(h_avg.r, 2.0))),
					sqrt((pow(v_avg.g, 2.0) + pow(h_avg.g, 2.0))),
					sqrt((pow(v_avg.b, 2.0) + pow(h_avg.b, 2.0))),
					0.0);
//			ft_putnbr(pxl.r + pxl.g + pxl.b);
//			ft_putstr(" <- red\n");
//			if (pxl.r + pxl.g + pxl.b < 2.0)
			if (pxl.r > 40.0)
			{
				mlx_put_pxl_img(e->ly_img, new_clr(0.0, 0.0, 0.0, 0.0), x, y);
			}
//			else
//			{
//				ft_putstr("ALPHA___\n");
//				mlx_put_pxl_img(e->ly_img, new_clr(0.0, 0.0, 0.0, 255.0), x, y);
//			}
			++x;
		}
		++y;
	}
}

void			projection(t_env *e)
{
	t_thread		thend[N_THREAD];
	pthread_t		threads[N_THREAD];
	int				i;

	i = -1;
	while (++i < N_THREAD)
	{
		thend[i].e = e;
		thend[i].id = i;
		if (pthread_create(threads + i, NULL,
				(void *)&draw_render, (void *)(thend + i)) != 0)
			ft_panic(e, "error: can not create a tread\n");
	}
	i = -1;
	while (++i < N_THREAD)
		if (pthread_join(threads[i], NULL) != 0)
			ft_panic(e, "error: can not join treads\n");
}
