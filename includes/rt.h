/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:09:19 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/12 13:22:53 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "rt_ts.h"
# define WIN_W 980
# define WIN_H 720

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	void			*render;
	char			*img;
	t_rtv1			core;
	unsigned char	aa;
	char			on;
}				t_env;

void			screenshot(char *img);

int				init_env(t_env *e);
void			ft_raytracer(t_env *e);
void			projection(t_env *e);
#endif
