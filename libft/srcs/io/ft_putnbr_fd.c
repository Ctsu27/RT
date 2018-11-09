/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:33:44 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/12 11:32:14 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ioft.h"

static void	ft_rec_putnbr_fd(unsigned int nb, int fd)
{
	if (nb / 10 != 0)
		ft_rec_putnbr_fd(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_rec_putnbr_fd(-n, fd);
	}
	else
		ft_rec_putnbr_fd(n, fd);
}
