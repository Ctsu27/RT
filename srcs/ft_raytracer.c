/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:25:18 by kehuang           #+#    #+#             */
/*   Updated: 2019/01/05 00:31:00 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <time.h>
#include "rt.h"
#include "parser.h"
#include "libft.h"
#include "mlx.h"
#include "key_mlx.h"

unsigned int	g_state = 1;

static void	mlx_free(t_env *e, int ret)
{
	if (ret & 0x08)
		mlx_destroy_image(e->mlx, e->render);
	if (ret & 0x04)
		mlx_destroy_window(e->mlx, e->win);
}

static int	suicide(t_env *e)
{
	free_lst(&e->core);
	mlx_free(e, 0x0e);
	exit(0);
	return (0);
}

static int	key_realease(int key, t_env *e)
{
	if (key == K_ESC)
		suicide(e);
	else if (key == K_F12)
		screenshot(e->img);
	return (0);
}

static void	move_cam(int key, t_env *e)
{
	t_cam	c;

	c = e->core.cam;
	if (key == K_W)
		e->core.cam.ray.pos = add_vec3(c.ray.pos,
				rot_vec3(norm_vec3(c.ray.dir), c.rotate));
	else if (key == K_S)
		e->core.cam.ray.pos = add_vec3(c.ray.pos,
				rot_vec3(norm_vec3(mul_vec3(c.ray.dir, -1.0)), c.rotate));
	else if (key == K_A)
		e->core.cam.ray.pos = add_vec3(c.ray.pos,
				rot_vec3(norm_vec3(mul_vec3(c.ray.dir, -1.0)),
					add_vec3(c.rotate, new_vec3(0.0, 90.0, 0.0))));
	else if (key == K_D)
		e->core.cam.ray.pos = add_vec3(c.ray.pos,
				rot_vec3(norm_vec3(mul_vec3(c.ray.dir, -1.0)),
					add_vec3(c.rotate, new_vec3(0.0, -90.0, 0.0))));
	else if (key == K_X)
		e->core.cam.ray.pos = add_vec3(c.ray.pos, new_vec3(0.0, 1.0, 0.0));
	else if (key == K_SPACE)
		e->core.cam.ray.pos = add_vec3(c.ray.pos, new_vec3(0.0, -1.0, 0.0));
}

static void	rotate_cam(int key, t_env *e)
{
	static double const	offs = 1.0;

	if (key == K_ARROW_L)
		e->core.cam.rotate.y -= offs;
	else if (key == K_ARROW_UP)
		e->core.cam.rotate.x += offs;
	else if (key == K_ARROW_DO)
		e->core.cam.rotate.x -= offs;
	else if (key == K_ARROW_R)
		e->core.cam.rotate.y += offs;
}

static int	key_press(int key, t_env *e)
{
	if (key == K_A || key == K_W || key == K_S || key == K_D
			|| key == K_X || key == K_SPACE)
	{
		g_state = 0;
		move_cam(key, e);
		projection(e);
		mlx_put_image_to_window(e->mlx, e->win, e->render, 0, 0);
	}
	else if (key == K_ARROW_L || key == K_ARROW_UP
			|| key == K_ARROW_DO || key == K_ARROW_R)
	{
		g_state = 0;
		rotate_cam(key, e);
		projection(e);
		mlx_put_image_to_window(e->mlx, e->win, e->render, 0, 0);
	}
	else if (key == K_RETURN && g_state != 1)
	{
		g_state = 1;
		projection(e);
		mlx_put_image_to_window(e->mlx, e->win, e->render, 0, 0);
	}
	return (0);
}

static int	put_render(t_env const *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->render, 0, 0);
	return (0);
}

void		ft_raytracer(t_env *e)
{
	int		ret;

	if ((ret = init_env(e)) != 0)
		return (mlx_free(e, ret));
	srand(time(NULL));
	projection(e);
	mlx_expose_hook(e->win, put_render, e);
	mlx_key_hook(e->win, key_realease, e);
	mlx_hook(e->win, 2, 3, key_press, e);
	mlx_hook(e->win, 17, 1L << 17, suicide, e);
	mlx_loop(e->mlx);
}
