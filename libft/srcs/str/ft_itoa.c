/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:30:25 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:30:30 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nbrlen(int n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_neg_itoa(char *dest, int index, unsigned int n)
{
	n = -n;
	while (index > 0)
	{
		dest[index - 1] = n % 10 + '0';
		n = n / 10;
		index--;
	}
	dest[0] = '-';
}

char		*ft_itoa(int n)
{
	char	*dest;
	int		index;

	index = ft_nbrlen(n);
	if ((dest = (char *)malloc(sizeof(*dest) * (index + 1))) == NULL)
		return (NULL);
	dest[index] = '\0';
	if (n < 0)
		ft_neg_itoa(dest, index, n);
	else
	{
		while (index > 0)
		{
			dest[index - 1] = n % 10 + '0';
			n = n / 10;
			index--;
		}
	}
	return (dest);
}
