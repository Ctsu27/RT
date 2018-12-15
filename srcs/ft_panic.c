/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_panic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:49:15 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/15 13:49:40 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include "mlx.h"
#include "ioft.h"
#include "parser.h"

void			ft_panic(t_env *e, char const *msg)
{
	mlx_destroy_image(e->mlx, e->render);
	mlx_destroy_window(e->mlx, e->win);
	free_lst(&e->core);
	if (msg != NULL)
		ft_putstr_fd(msg, 2);
	exit(-1);
}
