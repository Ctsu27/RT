/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:09:19 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/27 17:32:44 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "rt_ts.h"
# include <SDL.h>
# define WIN_W 980
# define WIN_H 720

typedef struct	s_env
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		evt;
	t_rtv1			core;
	unsigned char	aa;
	char			on;
}				t_env;

int				init_env(t_env *e);
void			ft_raytracer(t_env *e);
void			projection(t_env *e);
#endif
