/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufranco <lufranco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:28:05 by lufranco          #+#    #+#             */
/*   Updated: 2018/12/12 13:23:52 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "rt.h"
#include "ioft.h"

static void	bmp_pixel(int fd, char *img)
{
	int		size_line;
	int		i;
	int		j;

	size_line = WIN_W * 4;
	j = WIN_H;
	while (--j >= 0)
	{
		i = 0;
		while (i < size_line)
		{
			ft_putchar_fd(img[j * size_line + i], fd);
			ft_putchar_fd(img[j * size_line + i + 1], fd);
			ft_putchar_fd(img[j * size_line + i + 2], fd);
			i += 4;
		}
	}
}

static int	bmp_size(int i, int fd, unsigned int size, unsigned int len)
{
	if (i == 2)
	{
		ft_putchar_fd((size & 0xff), fd);
		ft_putchar_fd(((size >> 8) & 0xff), fd);
		ft_putchar_fd(((size >> 16) & 0xff), fd);
		ft_putchar_fd(((size >> 24) & 0xff), fd);
		return (i + 3);
	}
	len = WIN_W;
	ft_putchar_fd(len & 0xff, fd);
	ft_putchar_fd((len >> 8) & 0xff, fd);
	ft_putchar_fd((len >> 16) & 0xff, fd);
	ft_putchar_fd((len >> 24) & 0xff, fd);
	len = WIN_H;
	ft_putchar_fd(len & 0xff, fd);
	ft_putchar_fd((len >> 8) & 0xff, fd);
	ft_putchar_fd((len >> 16) & 0xff, fd);
	ft_putchar_fd((len >> 24) & 0xff, fd);
	return (i + 7);
}

static int	bmp_const(int i, int fd, unsigned int size)
{
	if (i == 10)
		ft_putchar_fd(54, fd);
	else if (i == 14)
		ft_putchar_fd(40, fd);
	else if (i == 26)
		ft_putchar_fd(1, fd);
	else if (i == 28)
		ft_putchar_fd(24, fd);
	else if (i == 40 || i == 44)
		ft_putchar_fd(0b00110000, fd);
	else if (i == 41 || i == 45)
		ft_putchar_fd(0b10110001, fd);
	else if (i == 34)
	{
		ft_putchar_fd(((size - 54) & 0xff), fd);
		ft_putchar_fd((((size - 54) >> 8) & 0xff), fd);
		ft_putchar_fd((((size - 54) >> 16) & 0xff), fd);
		ft_putchar_fd((((size - 54) >> 24) & 0xff), fd);
		return (i + 3);
	}
	else
		ft_putchar_fd(0, fd);
	return (i);
}

void		screenshot(char *img)
{
	unsigned int	size;
	unsigned int	len;
	int				fd;
	int				i;

	if ((fd = open("screenshot.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
		return ;
	ft_putstr_fd("BM", fd);
	size = 54 + (WIN_W * WIN_H * 3);
	len = 0;
	i = 1;
	while (++i < 54)
	{
		if (i == 18 || i == 2)
			i = bmp_size(i, fd, size, len);
		else
			i = bmp_const(i, fd, size);
	}
	bmp_pixel(fd, img);
	close(fd);
}
