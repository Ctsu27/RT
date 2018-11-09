/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_slst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:38:54 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/15 20:30:48 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "slst.h"

t_slst	*new_slst(void (*lst_data_init)(void **dest, void const *src),
		void const *data)
{
	t_slst	*lst;

	if (lst_data_init)
	{
		if (!(lst = (t_slst *)malloc(sizeof(t_slst))))
			return (NULL);
		if (data)
			lst_data_init(&lst->data, data);
		else
			lst->data = NULL;
		lst->n = NULL;
		return (lst);
	}
	return (NULL);
}
