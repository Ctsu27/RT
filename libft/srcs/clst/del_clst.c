/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_clst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:41:06 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/06 11:08:21 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "clst.h"

void	del_node_clst(t_clst *node, void (*lst_data_del)(void **data))
{
	t_clst	*ptr[2];

	if (node && lst_data_del)
	{
		ptr[0] = node->p;
		ptr[1] = node->n;
		if (node->p)
			node->p->n = ptr[1];
		if (node->n)
			node->n->p = ptr[0];
		node->p = NULL;
		node->n = NULL;
		lst_data_del(&node->data);
		free(node);
	}
}

void	del_clst(t_clst *head, void (*lst_data_del)(void **data))
{
	t_clst	*ptr;
	t_clst	*node;

	if (head)
	{
		ptr = head->n;
		while (ptr != head)
		{
			node = ptr;
			ptr = ptr->n;
			del_node_clst(node, lst_data_del);
		}
		del_node_clst(head, lst_data_del);
	}
}
