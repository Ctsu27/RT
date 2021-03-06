/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:33:49 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:33:52 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(const char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i > 0)
	{
		write(1, s, (i > 4096) ? 4096 : i);
		i -= (i > 4096) ? 4096 : i;
	}
}
