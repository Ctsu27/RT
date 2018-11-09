/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:25:00 by kehuang           #+#    #+#             */
/*   Updated: 2018/08/21 19:32:33 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int.h"

static int	alloc_light(t_rtv1 *core)
{
	t_light	*ptr;
	t_light	*node;

	if ((node = (t_light *)malloc(sizeof(*node))) == NULL)
		return (-1);
	node->next = NULL;
	node->pos.x = 0.0;
	node->pos.y = 0.0;
	node->pos.z = 0.0;
	node->clr.r = 255.0;
	node->clr.g = 255.0;
	node->clr.b = 255.0;
	node->clr.a = 0.0;
	ptr = core->light;
	if (ptr != NULL)
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = node;
	}
	else
		core->light = node;
	return (0);
}

static int	alloc_data_obj(t_poly *obj, unsigned int mask)
{
	if (mask & KEY_PLANE)
	{
		if ((obj->data = malloc(sizeof(t_plane))) == NULL)
			return (-1);
	}
	else if (mask & KEY_SPHERE)
	{
		if ((obj->data = malloc(sizeof(t_sphere))) == NULL)
			return (-1);
	}
	else if (mask & (KEY_CONE | KEY_CYLINDER))
	{
		if ((obj->data = malloc(sizeof(t_cone))) == NULL)
			return (-1);
	}
	return (0);
}

static int	get_obj_type(int type_mask)
{
	if (type_mask & KEY_SPHERE)
		return (TYPE_SPHERE);
	if (type_mask & KEY_CONE)
		return (TYPE_CONE);
	if (type_mask & KEY_CYLINDER)
		return (TYPE_CYLINDER);
	return (TYPE_PLANE);
}

static int	alloc_obj(t_rtv1 *core)
{
	t_poly	*ptr;
	t_poly	*node;

	if ((node = (t_poly *)malloc(sizeof(*node))) == NULL)
		return (-1);
	node->next = NULL;
	node->type = get_obj_type(core->mask);
	if (alloc_data_obj(node, core->mask) == -1)
		exit(EXIT_FAILURE);
	node->clr.r = 0.0;
	node->clr.g = 0.0;
	node->clr.b = 0.0;
	node->clr.a = 0.0;
	ptr = core->objs;
	if (ptr != NULL)
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = node;
	}
	else
		core->objs = node;
	return (0);
}

void		alloc_lst(t_rtv1 *core)
{
	if (core->mask & KEY_LIGHT)
	{
		if (alloc_light(core) == -1)
		{
			ft_putstr_fd("error: allocation failed\n", 2);
			free_lst(core);
			exit(EXIT_FAILURE);
		}
	}
	else if (core->mask & (KEY_PLANE | KEY_SPHERE | KEY_CONE | KEY_CYLINDER))
		if (alloc_obj(core) == -1)
		{
			ft_putstr_fd("error: allocation failed\n", 2);
			free_lst(core);
			exit(EXIT_FAILURE);
		}
}
