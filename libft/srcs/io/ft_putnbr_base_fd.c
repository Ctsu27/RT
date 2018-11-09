/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 08:44:57 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/20 15:22:55 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ioft.h"

static void	ft_rec_putnbr(unsigned int nb, int base, int fd)
{
	int		tmp;

	if (nb / base != 0)
		ft_rec_putnbr(nb / base, base, fd);
	tmp = nb % base;
	ft_putchar_fd(tmp + ((tmp < 10) ? '0' : 'a' - 10), fd);
}

void		ft_putnbr_base_fd(int n, int base, int fd)
{
	if (base < 2 || base > 16 || fd < 0)
		return ;
	if (n < 0 && base == 10)
	{
		ft_putchar('-');
		ft_rec_putnbr(-n, base, fd);
	}
	else
		ft_rec_putnbr(n, base, fd);
}
