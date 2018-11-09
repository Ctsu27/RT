/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:37:47 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/15 21:04:34 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLST_H
# define SLST_H

typedef struct	s_slst
{
	void			*data;
	struct s_slst	*n;
}				t_slst;

t_slst	*new_slst(void (*lst_data_init)(void **dest, void const *src),
		void const *data);
void	pbeg_slst(t_slst **head, t_slst *node);
void	pend_slst(t_slst **head, t_slst *node);
//void	del_node_slst(t_slst *node, void (*lst_data_del)(void **data));
void	del_slst(t_slst **head, void (*lst_data_del)(void **data));
#endif
