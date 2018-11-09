/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:56:55 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 11:27:06 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_ts.h"

static void	unit_atod(t_cur *fcur, char *str, double *val)
{
	if (str[fcur->i] >= '0' && str[fcur->i] <= '9')
	{
		while (str[fcur->i] >= '0' && str[fcur->i] <= '9')
		{
			*val = (*val * 10) + (str[fcur->i++] - '0');
			fcur->x++;
		}
	}
	else
		json_error(fcur, 5);
}

static void	floating_atod(t_cur *fcur, char *str, double *val)
{
	double			div;

	div = 0.1;
	if (str[fcur->i] == '.')
	{
		fcur->x++;
		if (str[++fcur->i] >= '0' && str[fcur->i] <= '9')
			while (str[fcur->i] >= '0' && str[fcur->i] <= '9')
			{
				*val = *val + ((str[fcur->i] - '0') * div);
				div = div / 10;
				fcur->i++;
				fcur->x++;
			}
		else
			json_error(fcur, 5);
	}
}

void		ft_atod(t_cur *fcur, char *str, double *val)
{
	unsigned char	neg;

	*val = 0.0;
	while (str[fcur->i] == '\t' || str[fcur->i] == ' ' || str[fcur->i] == '\n'
			|| str[fcur->i] == '\r' || str[fcur->i] == '\f'
			|| str[fcur->i] == '\v')
	{
		fcur->i++;
		fcur->x++;
	}
	if ((neg = (str[fcur->i] == '-')) || str[fcur->i] == '+')
	{
		fcur->i++;
		fcur->x++;
	}
	unit_atod(fcur, str, val);
	floating_atod(fcur, str, val);
	*val = (neg == 0) ? *val : *val * -1;
}
