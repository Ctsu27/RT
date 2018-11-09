/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:36:33 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/12 11:50:06 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "booleanft.h"

static int	ft_len(const char *str)
{
	int		i;
	int		j;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	j = i;
	while (str[j] != '\0')
		j++;
	j--;
	while (ft_iswhitespace(str[j]))
		j--;
	return ((i <= j) ? j + 1 - i : 0);
}

char		*ft_strtrim(char const *s)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	len = ft_len(s);
	i = 0;
	j = 0;
	if ((dest = (char *)malloc(sizeof(*dest) * (len + 1))) == NULL)
		return (NULL);
	while (ft_iswhitespace(s[i]))
		i++;
	while (j < len)
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
