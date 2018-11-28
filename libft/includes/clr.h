/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:51:18 by kehuang           #+#    #+#             */
/*   Updated: 2018/11/16 12:27:38 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLR_H
# define CLR_H

typedef struct	s_clr
{
	double	r;
	double	g;
	double	b;
	double	a;
}				t_clr;

t_clr			new_clr(double const r,
		double const g,
		double const b,
		double const a);
t_clr			add_clr(t_clr const a, t_clr const b);
t_clr			div_clr(t_clr const a, double const b);
t_clr			mul_clr(t_clr const a, double const b);
t_clr			sub_clr(t_clr const a, t_clr const b);
t_clr			lerp_clr(t_clr const a);

void			color_modifier(t_clr *pxl, int mod);
#endif
