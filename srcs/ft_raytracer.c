/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:25:18 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/10 11:36:29 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <time.h>
#include "rt.h"
#include "parser.h"
#include "libft.h"
#include "mlx.h"

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

static int	key_press_hook(int key, t_env *e)
{
	if (key == 53)
		suicide(e);
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
	mlx_key_hook(e->win, key_press_hook, e);
	mlx_hook(e->win, 17, 1L << 17, suicide, e);
	mlx_loop(e->mlx);
}
