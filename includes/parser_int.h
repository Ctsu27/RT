/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:23:14 by kehuang           #+#    #+#             */
/*   Updated: 2018/12/05 19:19:37 by kehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H
# include "rt_ts.h"

#include "ioft.h"

# define KEY_MAX		17
# define REBOUND_MAX	15
# define SAMPLE_MAX		4000

# define ID_MATERIAL	0
# define ID_FILTER		1
# define ID_GI			2

# define MASK_OBJ		0x100000000000000
# define MASK_STOP		0x8000000000000000

# define KEY_MAJOR		0xff00000000
# define KEY_MINOR		0xffff
# define KEY_OBJS		0xf00000000

# define HAS_CAM		0x1000000000000000

# define KEY_CAM		0x2000000000
# define KEY_LIGHT		0x1000000000

# define KEY_OBJECT		0xf00000000

# define KEY_SPHERE		0x800000000
# define KEY_CONE		0x400000000
# define KEY_CYLINDER	0x200000000
# define KEY_PLANE		0x100000000

# define KEY_GI			0x400
# define KEY_FILTER		0x200
# define KEY_ABSORPTION	0x100

# define KEY_DEPTH		0x80
# define KEY_MATERIAL	0x40
# define KEY_POS		0x20
# define KEY_ROT		0x10

# define KEY_FOV		0x8
# define KEY_COLOR		0x4
# define KEY_RAD		0x2
# define KEY_NORMAL		0x1

typedef struct	s_string
{
	char				*str;
	unsigned long int	size;
}				t_string;

int				ft_atod_sep(t_cur *fcur, double *val, char *cfile, char check);
int				check_sep_val(t_rtv1 *core, t_cur *fcur, char *cfile);

void			free_lst(t_rtv1 *core);
void			ft_zjump(t_cur *fcur, char *cfile);
void			json_error(t_cur *fcur, int const err);

void			alloc_lst(t_rtv1 *core);

void			take_obj_vec(t_rtv1 *core, t_vec3 **ptr);
void			take_light_pos(t_rtv1 *core, t_vec3 **ptr);
int				get_vec_value(t_vec3 *ptr, t_cur *fcur, char *cfile);

int				handle_double(t_rtv1 *core, t_cur *fcur, char *cfile);
int				handle_str(t_rtv1 *core, t_cur *fcur, char *cfile,
		unsigned long key);
int				get_clr(t_rtv1 *core, t_cur *fcur, char *cfile);

int				json_key(t_rtv1 *core, t_cur *fcur, char *cfile);
int				json_val(t_rtv1 *core, t_cur *fcur, char *cfile);
#endif
