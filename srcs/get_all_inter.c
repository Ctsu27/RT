/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:28:13 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:28:32 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "memoryft.h"

static void		insert_sort(t_inter *arr, int const size)
{
	t_inter	tmp;
	int		j;

	j = size - 1;
	while (j >= 0 && arr[j].t > arr[j + 1].t)
	{
		tmp = arr[j];
		arr[j] = arr[j + 1];
		arr[j + 1] = tmp;
		--j;
	}
}

static t_inter	get_inter_data(t_rtv1 const *core, t_ray const ray,
		t_poly *ptr, double const t)
{
	t_inter	hit;

	hit.obj = ptr;
	hit.pos = add_vec3(ray.pos, mul_vec3(ray.dir, t));
	hit.normal = core->normal_obj[hit.obj->type](hit.obj->data,
			(hit.obj->type != TYPE_PLANE) ? hit.pos : ray.dir);
	hit.t = t;
	return (hit);
}

t_inter			*get_all_inter(t_rtv1 const *core, t_ray const ray, int *size)
{
	t_poly	*ptr;
	double	t;
	t_inter	*hit;

	if ((hit = (t_inter *)ft_memalloc(sizeof(*hit) * core->n_obj)) != NULL)
	{
		ptr = core->objs;
		while (ptr != NULL)
		{
			if (core->inter_obj[ptr->type](ray, ptr->data, &t) && t > 0.01
					&& hit[*size].obj == NULL)
			{
				hit[*size] = get_inter_data(core, ray, ptr, t);
				insert_sort(hit, *size);
				*size += 1;
			}
			ptr = ptr->next;
		}
		if (*size == 0)
		{
			free(hit);
			return (NULL);
		}
	}
	return (hit);
}
