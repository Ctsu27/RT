/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 08:36:09 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/20 15:22:51 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ioft.h"

static void	ft_rec_putnbr(unsigned int nb, int base)
{
	int		tmp;

	if (nb / base != 0)
		ft_rec_putnbr(nb / base, base);
	tmp = nb % base;
	ft_putchar(tmp + ((tmp < 10) ? '0' : 'a' - 10));
}

void		ft_putnbr_base(int n, int base)
{
	if (base < 2 || base > 16)
		return ;
	if (n < 0 && base == 10)
	{
		ft_putchar('-');
		ft_rec_putnbr(-n, base);
	}
	else
		ft_rec_putnbr(n, base);
}
