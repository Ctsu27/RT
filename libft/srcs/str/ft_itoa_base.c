/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:30:33 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/12 11:38:09 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nb_len(int n, int base)
{
	int		len;

	len = ((n < 0 && base == 10) || n == 0);
	while (n != 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static char	*ft_convert(char *str, unsigned int n, int base, int index)
{
	static char	strbase[17] = "0123456789abcdef";
	int			idx;

	while (index > 0)
	{
		idx = n % base;
		str[index - 1] = strbase[idx];
		n = n / base;
		index--;
	}
	return (str);
}

char		*ft_itoa_base(int n, int base)
{
	char	*dest;
	int		index;

	if (base < 2 || base > 16)
		return (NULL);
	index = ft_nb_len(n, base);
	if ((dest = (char *)malloc(sizeof(*dest) * (index + 1))) == NULL)
		return (NULL);
	dest[index] = '\0';
	dest = ft_convert(dest, (n < 0) ? (unsigned int)-n
			: (unsigned int)n, base, index);
	if (n < 0 && base == 10)
		dest[0] = '-';
	return (dest);
}
