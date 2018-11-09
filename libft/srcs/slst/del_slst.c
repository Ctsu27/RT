/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_slst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:38:41 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/15 21:43:30 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "slst.h"

static void	del_node_slst(t_slst *node, void (*lst_data_del)(void **data))
//void	del_node_slst(t_slst *node, void (*lst_data_del)(void **data))
{
	if (node && lst_data_del)
	{
		lst_data_del(&node->data);
		free(node);
	}
}

void	del_slst(t_slst **head, void (*lst_data_del)(void **data))
{
	t_slst	*ptr;
	t_slst	*node;

	if (head && *head)
	{
		ptr = *head;
		while (ptr != NULL)
		{
			node = ptr;
			ptr = ptr->n;
			del_node_slst(node, lst_data_del);
		}
		*head = NULL;
	}
}
