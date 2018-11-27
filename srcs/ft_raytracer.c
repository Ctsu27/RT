/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:25:18 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/27 14:46:25 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <unistd.h>

static void	sdl_free(t_env *e, int ret)
{
	if (ret & 0x08)
		SDL_DestroyRenderer(e->render);
	if (ret & 0x04)
		SDL_DestroyWindow(e->win);
	if (ret & 0x02)
		SDL_Quit();
}

static void	handle_keyboard_event(t_env *e)
{
	if (e->evt.key.keysym.sym == SDLK_ESCAPE)
		e->on = 0;
	else if (e->evt.key.keysym.sym == SDLK_a)
	{
		if (e->aa < 3)
		{
			e->aa++;
			projection(e);
			SDL_RenderPresent(e->render);
		}
	}
	else if (e->evt.key.keysym.sym == SDLK_q)
	{
		if (e->aa > 0)
		{
			e->aa--;
			projection(e);
			SDL_RenderPresent(e->render);
		}
	}
	else if (e->evt.key.keysym.sym == SDLK_z)
	{
		if (e->core.cam.rebound > 0)
		{
			e->core.cam.rebound--;
			projection(e);
			SDL_RenderPresent(e->render);
		}
	}
	else if (e->evt.key.keysym.sym == SDLK_x)
	{
		if (e->core.cam.rebound < 7)
		{
			e->core.cam.rebound++;
			projection(e);
			SDL_RenderPresent(e->render);
		}
	}
}

static void	treat_event(t_env *e)
{
	if (e->evt.type == SDL_QUIT)
		e->on = 0;
	else if (e->evt.type == SDL_KEYDOWN)
		handle_keyboard_event(e);
}

void		ft_raytracer(t_env *e)
{
	int		ret;

	if ((ret = init_env(e)) != 0)
		return (sdl_free(e, ret));
	projection(e);
	while (e->on != FALSE)
		while (SDL_PollEvent(&e->evt))
			treat_event(e);
	sdl_free(e, 0x0e);
}
