/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rnew_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:10:27 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/05 17:25:11 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vec3.h"

t_vec3	rnew_vec3(void)
{
	static double const	range_max = 50.0;
	static double const	offset = 25.0;

	return (new_vec3((double)(((double)rand() / RAND_MAX * range_max) - offset),
				(double)(((double)rand() / RAND_MAX * range_max) - offset),
				(double)(((double)rand() / RAND_MAX * range_max) - offset)));
}
