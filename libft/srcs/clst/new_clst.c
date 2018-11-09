/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_clst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:35:53 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/05 16:44:28 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "clst.h"

t_clst	*new_clst(void (*lst_data_init)(void **dest, void const *src),
		void const *data)
{
	t_clst	*lst;

	if (lst_data_init)
	{
		if (!(lst = (t_clst *)malloc(sizeof(t_clst))))
			return (NULL);
		if (data)
			lst_data_init(&lst->data, data);
		else
			lst->data = NULL;
		lst->n = NULL;
		lst->p = NULL;
		return (lst);
	}
	return (NULL);
}
