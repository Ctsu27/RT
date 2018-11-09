/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:33:40 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/12 11:32:02 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ioft.h"

static void	ft_rec_putnbr(unsigned int nb)
{
	if (nb / 10 != 0)
		ft_rec_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

void		ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_rec_putnbr(-n);
	}
	else
		ft_rec_putnbr(n);
}
