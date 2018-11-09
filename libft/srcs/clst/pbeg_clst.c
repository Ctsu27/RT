/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbeg_clst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 20:20:01 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/05 20:22:23 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "clst.h"

void	pbeg_clst(t_clst **head, t_clst *node)
{
	t_clst	*tmp;

	if (head && *head)
		if ((*head)->n)
		{
			tmp = (*head)->n;
			(*head)->n = node;
			node->p = *head;
			node->n = tmp;
			tmp->p = node;
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
