/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 11:21:17 by kehuang           #+#    #+#             */
/*   Updated: 2018/07/24 11:21:18 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "rt_ts.h"

void	free_lst(t_rtv1 *core);
void	parser_json(t_rtv1 *core, int const fsize, char *cfile);
#endif
