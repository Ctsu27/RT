/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 11:37:05 by kehuang           #+#    #+#             */
/*   Updated: 2018/04/21 11:38:06 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_str2(char **arr)
{
	unsigned int	cur;

	cur = 0;
	while (arr[cur] != 0)
	{
		free(arr[cur]);
		cur++;
	}
	free(arr);
}
