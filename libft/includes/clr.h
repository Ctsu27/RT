/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:51:18 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/05 17:20:15 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLR_H
# define CLR_H

# define FILTER_SEPIA			0
# define FILTER_GRAY			1
# define FILTER_DEUTERANOMALY	2
# define FILTER_NONE			3

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
t_clr			clamp_clr(t_clr const a, double const max);

t_clr			modifier_clr(t_clr const pxl, int const filter);
#endif
