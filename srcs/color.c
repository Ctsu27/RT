/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufranco <lufranco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 02:03:09 by lufranco          #+#    #+#             */
/*   Updated: 2018/11/20 02:03:09 by lufranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gray(t_clr *pxl)
{
	double test;

	test = (pxl->r + pxl->g + pxl->b) / 765 * 255;
	pxl->r = test;
	pxl->g = test;
	pxl->b = test;
}

void	deuteranomaly(t_clr *pxl)
{
	double tmpR;
	double tmpG;
	double tmpB;

	tmpR = (pxl->r * 0.8) + (pxl->g * 0.2) + (pxl->b * 0);
	tmpG = (pxl->r * 0.258) + (pxl->g * 0.741) + (pxl->b * 0);
	tmpB = (pxl->r * 0) + (pxl->g * 0.141) + (pxl->b * 0.858);
	pxl->r = (tmpR > 255) ? 255 : tmpR;
	//pxl->r = (tmpR < 0) ? 0 : tmpR;
	pxl->g = (tmpG > 255) ? 255 : tmpG;
	//pxl->g = (tmpG < 0) ? 0 : tmpG;
	pxl->b = (tmpB > 255) ? 255 : tmpB;
	//pxl->b = (tmpB < 0) ? 0 : tmpB;

}

void	sepia(t_clr *pxl)
{
	double tmpR;
	double tmpG;
	double tmpB;

	tmpR = (pxl->r * 0.393) + (pxl->g * 0.769) + (pxl->b * 0.189);
	tmpG = (pxl->r * 0.349) + (pxl->g * 0.686) + (pxl->b * 0.168);
	tmpB = (pxl->r * 0.272) + (pxl->g * 0.534) + (pxl->b * 0.131);
	pxl->r = (tmpR > 255) ? 255 : tmpR;
	pxl->g = (tmpG > 255) ? 255 : tmpG;
	pxl->b = (tmpB > 255) ? 255 : tmpB;
}

void	color_modifier(t_clr *pxl, int mod)
{
	if (mod == 1)
		sepia(pxl);
	else if (mod == 2)
		deuteranomaly(pxl);
	else if (mod == 3)
		gray(pxl);
}
