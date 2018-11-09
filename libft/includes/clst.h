/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:44:09 by kehuang           #+#    #+#             */
/*   Updated: 2018/09/15 16:25:43 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLST_H
# define CLST_H

typedef struct	s_clst
{
	void			*data;
	struct s_clst	*n;
	struct s_clst	*p;
}				t_clst;

t_clst	*new_clst(void (*lst_data_init)(void **dest, void const *src),
		void const *data);
void	pbeg_clst(t_clst **head, t_clst *node);
void	pend_clst(t_clst **head, t_clst *node);
void	del_node_clst(t_clst *node, void (*lst_data_del)(void **data));
void	del_clst(t_clst *head, void (*lst_data_del)(void **data));
#endif
