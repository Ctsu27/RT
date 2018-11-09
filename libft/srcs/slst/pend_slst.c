/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pend_slst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:13:54 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/15 21:43:48 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "slst.h"

void	pend_slst(t_slst **head, t_slst *node)
{
	t_slst	*tmp;

	if (head && *head)
	{
		tmp = *head;
		while (tmp->n != NULL)
			tmp = tmp->n;
		tmp->n = node;
	}
	else if (head)
	{
		*head = node;
		(*head)->n = NULL;
	}
}
