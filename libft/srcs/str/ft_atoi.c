/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:29:32 by kehuang           #+#    #+#             */
/*   Updated: 2018/02/08 15:29:35 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int		result;
	int		i;
	int		n;

	result = 0;
	i = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\f'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if ((n = (str[i] == '-')) || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return ((n) ? -result : result);
}
