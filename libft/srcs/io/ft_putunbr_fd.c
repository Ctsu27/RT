/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 12:03:49 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/12 11:32:49 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ioft.h"

void		ft_putunbr_fd(unsigned int nb, int fd)
{
	if (nb / 10 != 0)
		ft_putunbr_fd(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}
