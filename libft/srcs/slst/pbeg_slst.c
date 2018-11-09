/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbeg_slst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:07:48 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/15 21:43:41 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "slst.h"

void	pbeg_slst(t_slst **head, t_slst *node)
{
	if (head && *head)
	{
		node->n = *head;
		*head = node;
	}
	else if (head)
	{
		*head = node;
		(*head)->n = NULL;
	}
}
