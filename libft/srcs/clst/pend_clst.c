/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pend_clst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:13:54 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/05 18:32:03 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "clst.h"

void	pend_clst(t_clst **head, t_clst *node)
{
	t_clst	*tmp;

	if (head && *head)
		if ((*head)->p)
		{
			tmp = (*head)->p;
			(*head)->p = node;
			node->n = *head;
			node->p = tmp;
			tmp->n = node;
		}
		else
		{
			(*head)->p = node;
			(*head)->n = node;
			node->n = *head;
			node->p = *head;
		}
	else if (head)
	{
		*head = node;
		(*head)->p = node;
		(*head)->n = node;
	}
}
