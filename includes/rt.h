/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:09:19 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:51:16 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "rt_ts.h"

# define WIN_W 980
# define WIN_H 720

# define N_THREAD 16

typedef struct	s_env
{
	t_rtv1			core;
	void			*mlx;
	void			*win;
	void			*render;
	char			*img;
	unsigned char	aa;
	char			on;
}				t_env;

typedef struct	s_thread
{
	t_env			*e;
	unsigned int	id;
}				t_thread;

void			screenshot(char *img);

void			ft_panic(t_env *e, char const *msg);
void			mlx_put_pxl_img(char *img, t_clr const c,
		int const x, int const y);

int				init_env(t_env *e);
void			ft_raytracer(t_env *e);
void			projection(t_env *e);
#endif
